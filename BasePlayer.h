#pragma once
#include "BaseClass.h"
#include "Field.h"

class BasePlayer :public BaseClass {
	Field* field;
	mino downMino;

	void DownMino() {
		//�������ɗ������Ȃ�������A���̏ꏊ�ɃZ�b�g����
		bool ableDown = true;
		for (int i = 0; i < downMino.blocksSize; ++i) {
			int x = downMino.block[i].pos.x;
			int y = downMino.block[i].pos.y;
			//���ɕ����������痎�����Ȃ�
			if (field->GetBlocks(x, y + 1).status != eBSNone) {
				ableDown = false;
			}
		}

		if (ableDown) {
			//������
			for (int i = 0; i < downMino.blocksSize; ++i) {
				downMino.block[i].pos.y++;
			}
		}
		else {
			//�����Ȃ��̂ŃZ�b�g����
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
