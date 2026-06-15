#include <DxLib.h>
#include "SceneTitle.h"
#include "InputManager.h"


TitleScene::TitleScene(void)
{
	imgTi = -1;
}

TitleScene::~TitleScene(void)
{
}

bool TitleScene::SystemInit(void)
{

	imgTi = LoadGraph("Screen/Title(Tentative).png");
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

	if ((prevSpaceKey == 1 && nowSpaceKey == 0)||(prevRightButton&&!nowRightButton)) nextSceneID = E_SCENE_MODE;
}

void TitleScene::Draw(void)
{

	DrawGraph(0, 0, imgTi, true);
}

bool TitleScene::Release(void)
{
	if (DeleteGraph(imgTi) == -1)return false;

	return true;
}
