#include <DxLib.h>
#include "SceneSelect.h"


SceneSelect::SceneSelect(void) 
{
	imgSe = -1;
}

SceneSelect::~SceneSelect(void) 
{

}

bool SceneSelect::SystemInit(void) 
{
	imgSe = LoadGraph("Screen/ModeSelect(Tentative).png");
	if (imgSe == -1)return false;

	return true;
}

void SceneSelect::GameInit(void) 
{
	nextSceneID = E_SCENE_SELECT;

}

void SceneSelect::UpDate(void) 
{

}

void SceneSelect::Draw(void) 
{
	DrawBox(0, 0, SCREEN_SIZE_HIG, SCREEN_SIZE_WID, GetColor(0, 0, 0), true);
	DrawGraph(0, 0, imgSe, true);
}

bool SceneSelect::Release(void) 
{
	if (DeleteGraph(imgSe) == -1)return false;

	return true;
}

