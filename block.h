#pragma once


enum eblockstatus {
	eBSNone,
	eBSExist,
	eBSErase
};

struct position {
	int x;
	int y;
};


struct block {
	eblockstatus status;
	bool downF;
	int color;
	position pos;
};
