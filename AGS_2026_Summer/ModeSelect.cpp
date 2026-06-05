#include "ModeSelect.h"
#include<DxLib.h>
#include "SceneManager.h"

ModeSelect::ModeSelect() {


	lv1img = -1;
	lv2img = -1;
	lv3img = -1;

}


ModeSelect::~ModeSelect() {

}



bool ModeSelect::SystemInit(void) {

	//画像読み込み
	lv1img = LoadGraph("image/GameLevel_Lv1.png");
	lv2img = LoadGraph("image/GameLevel_Lv2.png");
	lv3img = LoadGraph("image/GameLevel_Lv3.png");

	haikei = LoadGraph("Screen/haikei.png");
	if (haikei == -1)	return false;


	if (lv1img == -1 || lv2img == -1 || lv3img == -1)return false;

	x = SceneManager::SCREEN_SIZE_WID / 2;
	y = SceneManager::SCREEN_SIZE_HIG / 2;

	textx = SceneManager::SCREEN_SIZE_WID / 2.7;
	texty = (SceneManager::SCREEN_SIZE_HIG - (SceneManager::SCREEN_SIZE_HIG / 5));

	nowKeyInputU = nowKeyInputD = nowKeyInputL = nowKeyInputR = 0;
	prevKeyInputD = prevKeyInputL = prevKeyInputR = prevKeyInputU = 0;
	return true;
}

void ModeSelect::GameInit(void) {

	modeId = E_MODE_BASIC;
	diffId = E_DIFF_EASY;
	nextSceneID = E_SCENE_MODE;

}

void ModeSelect::Update(void) {

	Input();

}

void ModeSelect::Draw(void) {
	DrawRotaGraph(800, -40, 2.5, 0, haikei, true);



	ChangeDiffPicture();
	ChangeModePicture();
	BoarderTextUpdate();

}

bool ModeSelect::Release(void) {

	if (DeleteGraph(lv1img) == -1)return false;
	if (DeleteGraph(lv2img) == -1)return false;
	if (DeleteGraph(lv3img) == -1)return false;



	return true;

}


void ModeSelect::ChangeDiffPicture(void) {


	switch (diffId) {
	case E_DIFF_EASY:
		DrawRotaGraph(x, y, 5, 0, lv1img, true);

		break;
	case E_DIFF_HARD:
		DrawRotaGraph(x, y, 5, 0, lv2img, true);

		break;

	case E_DIFF_MASTER:
		DrawRotaGraph(x, y, 5, 0, lv3img, true);

		break;

	}
}


void ModeSelect::ChangeModePicture() {

	switch (modeId) {
	case E_MODE_BASIC:
		DrawFormatString(x, y, GetColor(0, 0, 0), "B");
		break;
	case E_MODE_ARENA:
		DrawFormatString(x, y, GetColor(0, 0, 0), "A");
		break;

	}

}


void ModeSelect::Input() {

		nowKeyInputL = CheckHitKey(KEY_INPUT_LEFT);

		nowKeyInputR = CheckHitKey(KEY_INPUT_RIGHT);

		nowKeyInputU = CheckHitKey(KEY_INPUT_UP);

		nowKeyInputD = CheckHitKey(KEY_INPUT_DOWN);
	
		nowSpaceKey = CheckHitKey(KEY_INPUT_SPACE);



	//左右操作でモード切替、上下操作で難易度変更
	if (nowKeyInputL==0&&prevKeyInputL==1) {
		modeId = (enum E_GAME_MODE_ID)((int)modeId + 1);
	}
	if (nowKeyInputR ==0&& prevKeyInputR == 1) {
		modeId = (enum E_GAME_MODE_ID)((int)modeId - 1);
	}
	if (nowKeyInputU == 0 && prevKeyInputU == 1) {
		diffId = (enum E_GAME_DIFF_ID)((int)diffId + 1);
	}
	if (nowKeyInputD == 0 && prevKeyInputD == 1) {
		diffId = (enum E_GAME_DIFF_ID)((int)diffId - 1);
	}

	if (nowSpaceKey == 0 && prevSpaceKey == 1) {
		SubmitGame();
	}


	if (modeId >= E_MODE_MAX)modeId = E_MODE_ARENA;

	if (modeId <= E_MODE_NON)modeId = E_MODE_BASIC;

	if (diffId >= E_DIFF_MAX) diffId = E_DIFF_MASTER;
	
	if (diffId <= E_DIFF_NON)diffId = E_DIFF_EASY;

	prevKeyInputL = nowKeyInputL;
	prevKeyInputR = nowKeyInputR;
	prevKeyInputU = nowKeyInputU;
	prevKeyInputD = nowKeyInputD;
	prevSpaceKey = nowSpaceKey;

}

int ModeSelect::GetBorderPoint() {

	switch (diffId) {
	case E_DIFF_EASY:
		return Easy;
		break;
	case E_DIFF_HARD:
		return Hard;
		break;
	case E_DIFF_MASTER:
		return Master;
		break;

	}

}

void ModeSelect::BoarderTextUpdate(void) {

	SetFontSize(48);

	int p = GetBorderPoint();
	switch (diffId)
	{
	case E_DIFF_EASY:
		DrawFormatString(textx, texty, GetColor(0,0 ,0 ), "BorderPoint%d", p);
		break;
	case E_DIFF_HARD:
		DrawFormatString(textx, texty, GetColor(0,0 , 0), "BorderPoint%d", p);
		break;
	case E_DIFF_MASTER:
		DrawFormatString(textx, texty, GetColor(0,0 ,0 ), "BorderPoint%d", p);
		break;
	}




}

void ModeSelect::SubmitGame(void){
	
	SetFontSize(48);
	switch (modeId) {
	case E_MODE_ARENA:
		Texttime = 400;
		if (Texttime > 0) {
			DrawFormatString(x, y, GetColor(0, 0, 0), "まだないよ");
		}
		break;
	case E_MODE_BASIC:
		nextSceneID = E_SCENE_GAME;

		break;
	}
	Texttime--;
}