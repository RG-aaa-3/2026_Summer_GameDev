#include "HowtoPlay.h"
#include <DxLib.h>
#include "InputManager.h"
#include "SceneManager.h"



HowtoPlay::HowtoPlay() {
	padimg = keyimg = -1;


}

HowtoPlay::~HowtoPlay() {



}

bool HowtoPlay::SystemInit() {

	padimg = LoadGraph("Screen/PADPlay.png");
	keyimg = LoadGraph("Screen/KeyPlay.png");

	if (padimg == -1 || keyimg == -1)return false;




	return true;
}


void HowtoPlay::GameInit(void) {

	nextSceneID = E_SCENE_HOW;

	nowimg = 1;
}

void HowtoPlay::UpDate(void) {

	InputManager& inputIns = InputManager::GetInstance();
	InputManager::JOYPAD_IN_STATE state =
		inputIns.GetJPadInputState(InputManager::JOYPAD_NO::PAD1);

	int analogKeyX = state.AKeyLX;


	//移動(上下左右キー)
	if (CheckHitKey(KEY_INPUT_LEFT) || analogKeyX < 0) {

		nowimg = 1;

	}
	if (CheckHitKey(KEY_INPUT_RIGHT) || analogKeyX > 0) {

		nowimg = 2;

	}
	if (CheckHitKey(KEY_INPUT_SPACE) || inputIns.IsPadBtnNew(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::RIGHT)) {
		nextSceneID = E_SCENE_MODE;
	}


}



void HowtoPlay::Draw(void) {

	switch (nowimg) {
	case 1:
		DrawGraph(150, 120, padimg, true);

		break;
	case 2:

		DrawGraph(150, 120, keyimg, true);

		break;
	}

	DrawFormatString(0, 1000, GetColor(255, 255, 255), "[B]or[SPACE]でモード選択へ");

}


bool HowtoPlay::Release(void) {

	if (DeleteGraph(padimg) == -1)return false;
	if (DeleteGraph(keyimg) == -1)return false;


	return true;
}
