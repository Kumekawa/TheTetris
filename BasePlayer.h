#pragma once
#include "BaseClass.h"
#include "Field.h"
#include "DxLib.h"

class BasePlayer :public BaseClass {
protected:
	Field* field;
	mino downMino;

	void DownMino() {
		bool nextF = false;
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
			//�����Ȃ�
			for (int i = 0; i < downMino.blocksSize; ++i) {
				downMino.block[i].status = eBSExist;
			}
			nextF = true;
		}
		field->SetMino(downMino,downMino.block[0].status);
		if (nextF) {
			SetNextMino();
		}
	}

	void SetNextMino() {
		downMino.SetBlocks((eminoshape)GetRand(minoShapeAmount - 1), field->GetCenter());
	}

	//�E�ɍs���Ȃ������true�ɁA���Ȃ�false��
	void Move(bool toRight) {
		int to = toRight ? 1 : -1;
		for (int i = 0; i < downMino.blocksSize; ++i) {
			int x = downMino.block[i].pos.x;
			int y = downMino.block[i].pos.y;

			if (field->GetBlocks(x + to, y).status == eBSExist) {
				return;
			}
		}
		for (int i = 0; i < downMino.blocksSize; ++i) {
			downMino.block[i].pos.x += to;
		}
	}

	virtual void MoveParallel() = 0;
public:

	void Initialize() {
		SetNextMino();
	}
	void Update() {
		MoveParallel();
		if (field->GetGameClockNow()) {
			if (field->GetFieldStatus() == eFSDown) {
				DownMino();
			}
		}
	}
	void Draw() {

	}

	void SetField(Field *field) {
		this->field = field;
	}
};
