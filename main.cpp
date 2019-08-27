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
	SetOutApplicationLogValidFlag(false);//���O���o�͂��Ȃ�

	ChangeWindowMode(TRUE);
	//�W���C�p�b�h�����܂��N�����Ȃ��ꍇ�͉��̊֐����g���Ă��������B
	SetUseJoypadVibrationFlag(FALSE);

	SetWindowSizeChangeEnableFlag(FALSE, FALSE); //���[�U�[���̃E�B���h�E�T�C�Y�ύX�s��
	//SetAlwaysRunFlag(TRUE); //�őO�ʂɂȂ���������
	SetGraphMode(MWS_XMAX, MWS_YMAX, 32); //�E�B���h�E�̍ő�T�C�Y�w��
	SetWindowSize(MWS_XMAX, MWS_YMAX); //�E�B���h�E�̃T�C�Y�w��

	//DxLib�̏���������
	if (DxLib_Init() == -1)
	{
		return -1;
	}
	//�`���ʂ𗠂�
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
	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}