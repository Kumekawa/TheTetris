#include "Field.h"
#include "MacroColor.h"

void Field::Down() {

}

void Field::Erase() {
	//消去開始時。消す行があるか調べる
	if (eraseCounter == 0) {
		//消すものが一つもなければステータスはeFSDownになる。
		int eraseLine = 0;
		for (int y = 0; y < MFS_YSIZE; ++y) {
			//消去フラグ。一つでも空白があればfalseになる。
			bool eraseF = true;
			for (int x = MFS_XOFFSET; x < MFS_XSIZE + MFS_XOFFSET; ++x) {
				if (blocks[x][y] == eBSNone) {
					eraseF = false;
					break;
				}
			}
			if (eraseF) {
				eraseLine++;
				for (int x = MFS_XOFFSET; x < MFS_XSIZE + MFS_XOFFSET; ++x) {
					blocks[x][y] = eBSErase;
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
			for (int y = 0; y < MFS_YSIZE; ++y) {
				if (blocks[x][y] == eBSErase) {
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
		for (int y = 0; y < MFS_YSIZE + 2; ++y) {
			blocks[x][y] = eBSExist;
		}
	}
	for (int x = MFS_XOFFSET; x < MFS_XSIZE + MFS_XOFFSET; ++x) {
		for (int y = 0; y < MFS_YSIZE; ++y) {
			blocks[x][y] = eBSExist;
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
		for (int j = 0; j < MFS_YSIZE; ++j) {
			int x = i - MFS_XOFFSET;
			int y = MFS_YSIZE * MFS_UNITSIZE / 2;

			int color = MC_WHITE;
			switch (blocks[i][j]) {
			case eBSErase:
				color = MC_RED;
				break;
			case eBSExist:
				color = MC_BLUE;
				break;
			case eBSNone:
			default:
				color = MC_WHITE;
				break;
			}

			DrawBox(x * MFS_UNITSIZE, j * MFS_UNITSIZE + y, (x + 1) * MFS_UNITSIZE, (j - 1) * MFS_UNITSIZE + y, color, 1);
		}
	}
}

void Field::SetMino(mino Mino) {
	for (int i = 0; i < 4; ++i) {
		blocks[Mino.blocks[i].x][Mino.blocks[i].y] = eBSExist;
	}
	eFieldStatus = eFSErase;
}

bool Field::GetGameClockNow() {
	return gameClockNow;
}
