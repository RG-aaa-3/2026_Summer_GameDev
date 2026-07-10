#include <DxLib.h>
#include "SceneTitle.h"
#include "InputManager.h"
#include "SceneManager.h"


TitleScene::TitleScene(void)
{
	imgTi = -1;
	yesimg = -1;
	noimg = -1;
}

TitleScene::~TitleScene(void)
{
}

bool TitleScene::SystemInit(void)
{

	imgTi = LoadGraph("Screen/Title.png");

	yesimg = LoadGraph("Screen/Yes.png");
	noimg = LoadGraph("Screen/No.png");

	if (yesimg == -1 || noimg == -1)return false;

	if (imgTi == -1)return false;

	return true;
}

void TitleScene::GameInit(void)
{
	nextSceneID = E_SCENE_TITLE;

	prevSpaceKey = nowSpaceKey = 0;
	prevRightButton = nowRightButton = false;

}

void TitleScene::UpDate(void)
{
	InputManager& inputIns = InputManager::GetInstance();
	InputManager::JOYPAD_IN_STATE state =
		inputIns.GetJPadInputState(InputManager::JOYPAD_NO::PAD1);

	prevRightButton = nowRightButton;
	nowRightButton = inputIns.IsPadBtnNew(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::RIGHT);

	prevSpaceKey = nowSpaceKey;
	nowSpaceKey = CheckHitKey(KEY_INPUT_SPACE);

	if (Quitkakunin == false && ((prevSpaceKey == 0 && nowSpaceKey == 1) || (prevRightButton && !nowRightButton))) nextSceneID = E_SCENE_MODE;


	if (CheckHitKey(KEY_INPUT_ESCAPE))Quitkakunin = true;

	if (Quitkakunin)GameQuitkakunin();

}

void TitleScene::Draw(void)
{
	if (Quitkakunin == false)SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawGraph(0, 0, imgTi, true);


	if (Quitkakunin)GameQuitkakuninDraw();

}

bool TitleScene::Release(void)
{
	if (DeleteGraph(imgTi) == -1)return false;

	return true;
}



void TitleScene::GameQuitkakunin() {
	nowSpaceKey = CheckHitKey(KEY_INPUT_SPACE);

	InputManager& inputIns = InputManager::GetInstance();
	InputManager::JOYPAD_IN_STATE state =
		inputIns.GetJPadInputState(InputManager::JOYPAD_NO::PAD1);

	int analogKeyX = state.AKeyLX;

	if (CheckHitKey(KEY_INPUT_RIGHT) || analogKeyX < 0)imgtrg = 2;
	if (CheckHitKey(KEY_INPUT_LEFT) || analogKeyX > 0)imgtrg = 1;

	prevSpaceKey = nowSpaceKey;

}

void TitleScene::GameQuitkakuninDraw() {

	// 背景を少し暗くする
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 120);

	DrawBox(
		0,
		0,
		1920,
		1080,
		GetColor(0, 0, 0),
		true
	);

	SetFontSize(62);
	DrawFormatString(SceneManager::SCREEN_SIZE_WID / 3, SceneManager::SCREEN_SIZE_HIG / 4,
		GetColor(255, 255, 255), "ゲームを終了しますか？");


	InputManager& inputIns = InputManager::GetInstance();
	switch (imgtrg) {
	case 1:			//Yesにソート
		DrawRotaGraph(SceneManager::SCREEN_SIZE_WID / 4, SceneManager::SCREEN_SIZE_HIG / 2, 1.5, 0, yesimg, true);
		DrawGraph(SceneManager::SCREEN_SIZE_WID - (SceneManager::SCREEN_SIZE_WID / 4), SceneManager::SCREEN_SIZE_HIG / 2, noimg, true);


		if (CheckHitKey(KEY_INPUT_SPACE) || inputIns.IsPadBtnNew(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::RIGHT))nextSceneID = E_SCENE_QUIT;


		break;
	case 2:			//Noにソート
		DrawRotaGraph(SceneManager::SCREEN_SIZE_WID - (SceneManager::SCREEN_SIZE_WID / 4), SceneManager::SCREEN_SIZE_HIG / 2, 1.5, 0, noimg, true);
		DrawGraph(SceneManager::SCREEN_SIZE_WID / 4, SceneManager::SCREEN_SIZE_HIG / 2, yesimg, true);

		if (CheckHitKey(KEY_INPUT_SPACE) || inputIns.IsPadBtnNew(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::RIGHT))Quitkakunin = false;

		break;
	}



}