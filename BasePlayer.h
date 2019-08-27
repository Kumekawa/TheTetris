#pragma once
#include "BaseClass.h"
#include "Field.h"

class BasePlayer :public BaseClass {
	Field* field;
	mino downMino;

	void DownMino() {
		//もし下に落ちられなかったら、その場所にセットする
		bool ableDown = true;
		for (int i = 0; i < downMino.blocksSize; ++i) {
			int x = downMino.block[i].pos.x;
			int y = downMino.block[i].pos.y;
			//下に物があったら落ちられない
			if (field->GetBlocks(x, y + 1).status != eBSNone) {
				ableDown = false;
			}
		}

		if (ableDown) {
			//落ちる
			for (int i = 0; i < downMino.blocksSize; ++i) {
				downMino.block[i].pos.y++;
			}
		}
		else {
			//落ちないのでセットする
			field->SetMino(downMino);
		}
	}

	virtual void MoveParallel() = 0;
public:

	void Initialize() {

	}
	void Update() {
		if (field->GetGameClockNow()) {
			DownMino();
		}
	}
	void Draw() {

	}
};
