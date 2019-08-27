#include "Field.h"
#include "MacroColor.h"

void Field::Down() {

}

void Field::Erase() {
	//消去開始時。消す行があるか調べる
	if (eraseCounter == 0) {
		//消すものが一つもなければステータスはeFSDownになる。
		int eraseLine = 0;
		for (int y = MFS_YOFFSET; y < MFS_YSIZE + MFS_YOFFSET; ++y) {
			//消去フラグ。一つでも空白があればfalseになる。
			bool eraseF = true;
			for (int x = MFS_XOFFSET; x < MFS_XSIZE + MFS_XOFFSET; ++x) {
				if (blocks[x][y].status == eBSNone) {
					eraseF = false;
					break;
				}
			}
			if (eraseF) {
				eraseLine++;
				for (int x = MFS_XOFFSET; x < MFS_XSIZE + MFS_XOFFSET; ++x) {
					blocks[x][y].status = eBSErase;
				}
			}
		}
		if (eraseLine == 0) {
			eFieldStatus = eFSDown;
		}
	}
	else if (eraseCounter == 1) {

	}
	else if (eraseCounter == 2) {
		//実際に消す処理
		for (int x = MFS_XOFFSET; x < MFS_XSIZE + MFS_XOFFSET; ++x) {
			for (int y = MFS_YOFFSET; y < MFS_YSIZE + MFS_YOFFSET; ++y) {
				if (blocks[x][y].status == eBSErase) {
					for (int k = y; k < MFS_YSIZE; ++k) {
						blocks[x][y] = blocks[x][y + 1];
					}
					--y;
				}
			}
		}
		eFieldStatus = eFSDown;
	}
	eraseCounter++;
}

void Field::GameTimeCount() {
	++gameTimer;
	if (gameTimer < gameSpeed) {
		gameClockNow = false;
	}
	else {
		gameClockNow = true;
		gameTimer = 0;
	}
}

Field::Field() {

}

void Field::Initialize() {
	for (int x = 0; x < MFS_XSIZE + MFS_XOFFSET * 2; ++x) {
		for (int y = 0; y < MFS_YSIZE + MFS_YOFFSET * 2; ++y) {
			blocks[x][y].status = eBSExist;
		}
	}
	for (int x = MFS_XOFFSET; x < MFS_XSIZE + MFS_XOFFSET; ++x) {
		for (int y = MFS_YOFFSET; y < MFS_YSIZE + MFS_YOFFSET; ++y) {
			blocks[x][y].status = eBSExist;
		}
	}

	eFieldStatus = eFSDown;
	gameClockNow = true;
	gameLevel = 1;
	gameSpeed = 30;
	gameTimer = 0;
}

void Field::Update() {
	GameTimeCount();
	if (GetGameClockNow()) {
		switch (eFieldStatus)
		{
		case eFSDown:
			Down();
			break;
		case eFSErase:
			Erase();
			break;
		default:
			break;
		}
	}
}

void Field::Draw() {
	for (int i = MFS_XOFFSET; i < MFS_XSIZE + MFS_XOFFSET; ++i) {
		for (int j = MFS_YOFFSET; j < MFS_YSIZE + MFS_YOFFSET; ++j) {
			int x = i - MFS_XOFFSET;
			int y = j - MFS_YOFFSET;
			int yOffset = MFS_UNITSIZE * (MFS_YSIZE - MFS_YOFFSET * 2) / 2;

			DrawBox(x * MFS_UNITSIZE, y * MFS_UNITSIZE + yOffset, (x + 1) * MFS_UNITSIZE, (y - 1) * MFS_UNITSIZE + yOffset, blocks[i][j].color, 1);
		}
	}
}

void Field::SetMino(mino Mino) {
	for (int i = 0; i < 4; ++i) {
		blocks[Mino.block[i].pos.x][Mino.block[i].pos.y].status = eBSExist;
	}
	eFieldStatus = eFSErase;
}

bool Field::GetGameClockNow() {
	return gameClockNow;
}

block Field::GetBlocks(int x, int y){
	return blocks[x][y];
}
