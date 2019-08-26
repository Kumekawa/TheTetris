#pragma once
#include "BaseClass.h"
#include "mino.h"

enum efieldstatus {
	eFSDown,
	eFSErase
};
enum eblockstatus {
	eBSNone,
	eBSExist,
	eBSErase
};

constexpr int MFS_XSIZE = 8;
constexpr int MFS_YSIZE = 20;

class Field :public BaseClass {
	eblockstatus bloacks[MFS_XSIZE][MFS_YSIZE];
	efieldstatus eFieldStatus;
	void Down() {

	}

	int eraseCounter;
	void Erase() {
		//�����J�n���B�����s�����邩���ׂ�
		if (eraseCounter == 0) {
			//�������̂�����Ȃ���΃X�e�[�^�X��eFSDown�ɂȂ�B
			int eraseLine = 0;
			for (int y = 0; y < MFS_YSIZE; ++y) {
				//�����t���O�B��ł��󔒂������false�ɂȂ�B
				bool eraseF = true;
				for (int x = 0; x < MFS_XSIZE; ++x) {
					if (bloacks[x][y] == eBSNone) {
						eraseF = false;
						break;
					}
				}
				if (eraseF) {
					eraseLine++;
					for (int x = 0; x < MFS_XSIZE; ++x) {
						bloacks[x][y] = eBSErase;
					}
				}
			}
			if (eraseLine == 0) {
				eFieldStatus = eFSDown;
			}
		}
		eraseCounter++;
	}
public:
	Field();
	void Update() {
		switch (eFieldStatus)
		{
		case eFSDown:
			break;
		case eFSErase:
			break;
		default:
			break;
		}
	}
	void Draw();
	void SetMino(mino Mino) {
		for (int i = 0; i < 4; ++i) {
			bloacks[Mino.blocks[i].x][Mino.blocks[i].y] = eBSExist;
		}
		eFieldStatus = eFSErase;
	}
};
