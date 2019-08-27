#include "DxLib.h"
#include "MacroWindowSize.h"
#include "DxLibAlways.h"
#include "DxLibEndEffect.h"
#include <vector>
using namespace std;

#include "Field.h"
#include "PlayerHuman.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetOutApplicationLogValidFlag(false);//ログを出力しない

	ChangeWindowMode(TRUE);
	//ジョイパッドがうまく起動しない場合は下の関数を使ってください。
	SetUseJoypadVibrationFlag(FALSE);

	SetWindowSizeChangeEnableFlag(FALSE, FALSE); //ユーザー側のウィンドウサイズ変更不可
	//SetAlwaysRunFlag(TRUE); //最前面にない時も動作
	SetGraphMode(MWS_XMAX, MWS_YMAX, 32); //ウィンドウの最大サイズ指定
	SetWindowSize(MWS_XMAX, MWS_YMAX); //ウィンドウのサイズ指定

	//DxLibの初期化処理
	if (DxLib_Init() == -1)
	{
		return -1;
	}
	//描画画面を裏に
	SetDrawScreen(DX_SCREEN_BACK);

	vector<BaseClass*> objects;

	Field field;
	objects.push_back(&field);

	PlayerHuman player;
	player.SetField(&field);
	objects.push_back(&player);

	for (int i = 0; i < objects.size(); ++i) {
		objects[i]->Initialize();
	}

	while (ProcessMessage() == 0)
	{
		for (int i = 0; i < objects.size(); ++i) {
			objects[i]->Update();
			objects[i]->Draw();
		}

		if (DxLibEndEffect(true)) {
			break;
		}
		DxLibAlways(true);
	}
	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}