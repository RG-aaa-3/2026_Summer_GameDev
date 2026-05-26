#include "Result.h"
#include <DxLib.h>
#include "GameScene.h"
#include <fstream>
#include <vector>
#include <algorithm>


Result::Result(void) {

	firstscore = 0;
	secondscore = 0;
	thirdscore = 0;
	fourcescore = 0;
	myscore = 0;
	prevscore = 0;

	prevNextKey = 0;
	nowNextKey = 0;



}

Result::~Result(void) {



}

bool Result::SystemInit() {

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

		SetFontSize(48);

		DrawFormatString(240, 80, GetColor(255, 255, 0), "1st:%d", firstscore);
		DrawFormatString(240, 160, GetColor(200, 200, 200), "2nd:%d", secondscore);
		DrawFormatString(240, 240, GetColor(204, 102, 0), "3rd:%d", thirdscore);
		DrawFormatString(240, 320, GetColor(0, 180, 0), "4th:%d", fourcescore);
		DrawFormatString(240, 400, GetColor(255, 255, 255), "You:%d", myscore);
	

}


bool Result::Release() {



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

void Result::SetScore(int score)
{
	myscore = score;
	HighScoreUpdate();
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