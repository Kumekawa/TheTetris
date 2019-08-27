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
//‰ñ“]‚âˆÚ“®‚Éˆ—‚µ‚â‚·‚¢‚æ‚¤‰¡•‚ğ‘å‚«‚ß‚É‚Æ‚é
constexpr int MFS_XOFFSET = 5;

constexpr int MFS_UNITSIZE = 20;

class Field :public BaseClass {
	eblockstatus blocks[MFS_XSIZE + MFS_XOFFSET * 2][MFS_YSIZE + 2] = {};
	efieldstatus eFieldStatus = eFSDown;

	int gameLevel = 1;
	int gameSpeed = 30;
	int gameTimer = 0;
	bool gameClockNow = true;

	int eraseCounter = 0;

	void Down();

	void Erase();

	void GameTimeCount();
public:
	Field();
	void Initialize();

	void Update();
	void Draw();
	void SetMino(mino Mino);

	bool GetGameClockNow();
};
