#include "mino.h"
#include "MacroColor.h"

void mino::SetBlocks(eminoshape eMinoShape, position center) {
	position *pos = GetShapePosition(eMinoShape, center, eD_up);
	for (int i = 0; i < 4; ++i) {
		block[i].pos = pos[i];
		block[i].color = MC_BLUE;
		block[i].status = eBSDown;
	}
}

position * GetShapePosition(eminoshape eMinoShape, position center, edirection eDirection) {
	position pos[4];
	for (int i = 0; i < 4; ++i) {
		pos[i] = center;
	}

	int k = 1;
	for (int i = 0; i < shapeSize; ++i) {
		for (int j = 0; j < shapeSize; ++j) {
			if (minoShapes[eMinoShape][eDirection][j][i] == 1) {
				pos[k].x += i - shapeSize / 2;
				pos[k].y += j - shapeSize / 2;
				k++;
				if (k >= 4) {
					return pos;
				}
			}
		}
	}
}
