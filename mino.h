#pragma once
#include "block.h"


struct mino {
	static const int blocksSize = 4;
	//0個目をセンターとする。
	block block[blocksSize];
};

