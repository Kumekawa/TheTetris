#include "PlayerHuman.h"
#include "DxLib.h"

void PlayerHuman::MoveParallel() {
	if (CheckHitKey(KEY_INPUT_A)) {
		Move(false);
	}
	if (CheckHitKey(KEY_INPUT_D)) {
		Move(true);
	}


}
