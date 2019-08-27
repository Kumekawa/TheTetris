#pragma once


enum eblockstatus {
	eBSNone,
	eBSDown,
	eBSExist,
	eBSErase
};

struct position {
	int x;
	int y;
};


struct block {
	eblockstatus status;
	int color;
	position pos;
};
