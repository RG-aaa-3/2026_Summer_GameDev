#include <DxLib.h>
#include "SceneTitle.h"

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

}

void TitleScene::UpDate(void)
{
	prevSpaceKey = nowSpaceKey;
	nowSpaceKey = CheckHitKey(KEY_INPUT_SPACE);

	if (prevSpaceKey == 1 && nowSpaceKey == 0);
	nextSceneID = E_SCENE_SELECT;
}

void TitleScene::Draw(void)
{

	// Ç‹Ç∏îwåiÇçïÇ≈ìhÇËÇ¬Ç‘Ç∑
	DrawBox(0, 0, SCREEN_SIZE_HIG,SCREEN_SIZE_WID, GetColor(0, 0, 0), true);
	DrawGraph(0, 0, imgTi, true);
}

bool TitleScene::Release(void)
{
	if (DeleteGraph(imgTi) == -1)return false;

	return true;
}
