#pragma once

struct position {
	int x;
	int y;
};

struct mino {
	//0個目をセンターとする。
	position blocks[4];
};

