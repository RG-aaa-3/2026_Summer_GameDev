#include "Result.h"
#include <DxLib.h>
#include "GameScene.h"
#include <fstream>
#include <vector>
#include <algorithm>
#include "ModeSelect.h"
#include "SceneManager.h"


Result::Result(void) {

	result = -1;

	firstscore = 0;
	secondscore = 0;
	thirdscore = 0;
	fourcescore = 0;
	myscore = 0;
	prevscore = 0;

	prevNextKey = 0;
	nowNextKey = 0;

	clear = false;


	mode = nullptr;

}

Result::~Result(void) {



}

bool Result::SystemInit() {

	result = LoadGraph("Screen/Result.png");
	if (result == -1)return false;

	LoadHighScoreFile();

	return true;
}




void Result::GameInit(){

	nextSceneID = E_SCENE_RESULT;

	prevNextKey = nowNextKey = 0;


}


void Result::Update() {


	prevNextKey = nowNextKey;
	nowNextKey = CheckHitKey(KEY_INPUT_SPACE);

	//アップトリガーで判断
	if (prevNextKey == 1 && nowNextKey == 0) {
		nextSceneID = E_SCENE_TITLE;
	}



}



void Result::Draw() {
	int p = borderPoint;

	DrawRotaGraph3(SceneManager::SCREEN_SIZE_WID / 2, SceneManager::SCREEN_SIZE_HIG / 2, 
		1024 / 2, 426 / 2, 1.875, 2.5, 0, result, false);

	

		SetFontSize(48);

		DrawFormatString(240, 80, GetColor(255, 255, 0), "1st:%d", firstscore);
		DrawFormatString(240, 160, GetColor(200, 200, 200), "2nd:%d", secondscore);
		DrawFormatString(240, 240, GetColor(204, 102, 0), "3rd:%d", thirdscore);
		DrawFormatString(240, 320, GetColor(0, 180, 0), "4th:%d", fourcescore);
		DrawFormatString(240, 400, GetColor(255, 255, 255), "You:%d", myscore);

		DrawFormatString(1590, 990, GetColor(255, 255, 255), "SPACE>Title");
	

		DrawFormatString(240, 500, GetColor(255, 0, 0),"BORDER:%d", p);
		if (clear)DrawFormatString(480, 160, GetColor(255, 0, 0),"LEVEL CLEAR!!");
		if (clear == false)DrawFormatString(480, 160, GetColor(0, 0, 0), "LEVEL FAILED...");

}


bool Result::Release() {

	if (DeleteGraph(result) == -1)return false;

	return true;
}

void Result::HighScoreUpdate()
{
	std::vector<int> scores;

	scores.push_back(firstscore);
	scores.push_back(secondscore);
	scores.push_back(thirdscore);
	scores.push_back(fourcescore);
	scores.push_back(myscore);

	std::sort(scores.begin(), scores.end(), std::greater<int>());

	firstscore = scores[0];
	secondscore = scores[1];
	thirdscore = scores[2];
	fourcescore = scores[3];

	SaveHighScoreFile();
}

void Result::SetResultData(int score, int border)
{
	myscore = score;
	borderPoint = border;

	HighScoreUpdate();
	IsBorderCleard();
}

bool Result::LoadHighScoreFile(void)
{
	std::ifstream file("data/highscore.txt");

	if (!file.is_open())
	{
		firstscore = 0;
		secondscore = 0;
		thirdscore = 0;
		fourcescore = 0;
		return false;
	}

	file >> firstscore;
	file >> secondscore;
	file >> thirdscore;
	file >> fourcescore;

	file.close();

	return true;
}

bool Result::SaveHighScoreFile(void)
{
	std::ofstream file("data/highscore.txt");

	if (!file.is_open())
	{
		return false;
	}

	file << firstscore << std::endl;
	file << secondscore << std::endl;
	file << thirdscore << std::endl;
	file << fourcescore << std::endl;

	file.close();

	return true;
}

void Result::IsBorderCleard(void) {

	if (myscore >= borderPoint) {
		clear = true;
	}
	else {
		clear = false;
	}
}