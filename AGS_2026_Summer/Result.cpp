#include "Result.h"
#include <DxLib.h>
#include "GameScene.h"
#include <fstream>
#include <vector>
#include <algorithm>
#include "ModeSelect.h"
#include "SceneManager.h"
#include <functional>



Result::Result(void) {

result = -1;

clearSe = -1;

failedSe = -1;

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

clearSe = LoadSoundMem("sound/StageClear.mp3");
failedSe = LoadSoundMem("sound/StageFailed.mp3");


LoadHighScoreFile();
LoadArenaFloorFile();


 return true;

}









void Result::GameInit() {

nextSceneID = E_SCENE_RESULT;

 prevNextKey = nowNextKey = 0;

 if (clear == true) 
 {
	 PlayMusic("sound/StageClear.mp3", DX_PLAYTYPE_BACK);
 }
 else if(clear == false) 
 {
	 PlayMusic("sound/StageFailed.mp3", DX_PLAYTYPE_BACK);
 }

}





void Result::Update() {

 prevNextKey = nowNextKey;

 nowNextKey = CheckHitKey(KEY_INPUT_SPACE);



//アップトリガーで判断
 if (prevNextKey == 1  && nowNextKey == 0) {

	 if (CheckHitKey(KEY_INPUT_SPACE)) 
	 {
		 StopMusic();
		 nextSceneID = E_SCENE_TITLE;
	 }


	 if (GetJoypadInputState(DX_INPUT_KEY_PAD1) & KEY_INPUT_B)
	 {
		 StopMusic();
		 nextSceneID = E_SCENE_TITLE;
	 }


	}



}







void Result::Draw() {



	if (resultModeId == E_MODE_ARENA)
	{
		DrawFormatString(
			240,
			80,
			GetColor(255, 255, 0),
			"1st : %d F",
			firstFloor
		);

		DrawFormatString(
			240,
			160,
			GetColor(200, 200, 200),
			"2nd : %d F",
			secondFloor
		);

		DrawFormatString(
			240,
			240,
			GetColor(204, 102, 0),
			"3rd : %d F",
			thirdFloor
		);

		DrawFormatString(
			240,
			320,
			GetColor(0, 180, 0),
			"4th : %d F",
			fourthFloor
		);

		DrawFormatString(
			240,
			460,
			GetColor(255, 255, 255),
			"YOU : %d F",
			arenaFloor
		);


		return;
	}


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

	if (clearSe != -1) 
	{
		DeleteSoundMem(clearSe);
		clearSe = -1;
	}

	if (failedSe != -1)
	{
		DeleteSoundMem(failedSe);
		failedSe = -1;
	}

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



void Result::SetResultData(
	int score,
	int border,
	E_GAME_MODE_ID mode,
	E_GAME_DIFF_ID diff,
	int floor
)
{
	myscore = score;
	borderPoint = border;
	resultDiffId = diff;
	resultModeId = mode;
	
	arenaFloor = floor;

	if (resultModeId == E_MODE_ARENA)
	{
		ArenaFloorRankUpdate();
	}
	else
	{
		HighScoreUpdate();
		IsBorderCleard();
	}
}


bool Result::LoadHighScoreFile(void)

{
	switch (resultDiffId) {
	case E_DIFF_EASY:
	{
		std::ifstream file("data/Easyscore.txt");


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
		break;
	}
	case E_DIFF_HARD:

	{
		std::ifstream file("data/Hardscore.txt");


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
		break;
	}

	case E_DIFF_MASTER:

	{
		std::ifstream file("data/Masterscore.txt");


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
		break;
	}
	}
}



bool Result::SaveHighScoreFile(void)

{
	

	switch (resultDiffId) {
	case E_DIFF_EASY:
	{
		std::ofstream file("data/Easyscore.txt");

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
		break;
	}
	case E_DIFF_HARD:
	{
		std::ofstream file("data/Hardscore.txt");

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
		break;
	}
	case E_DIFF_MASTER:

	{
		std::ofstream file("data/Masterscore.txt");

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
		break;
	}
	}
}



void Result::IsBorderCleard(void) {

	if (myscore >= borderPoint) {

		clear = true;

	}

	else {

		clear = false;


	}

}

bool Result::LoadArenaFloorFile(void)
{
	std::ifstream file("data/arenafloor.txt");

	if (!file.is_open())
	{
		firstFloor = 0;
		secondFloor = 0;
		thirdFloor = 0;
		fourthFloor = 0;
		return false;
	}

	file >> firstFloor;
	file >> secondFloor;
	file >> thirdFloor;
	file >> fourthFloor;

	file.close();

	return true;
}

bool Result::SaveArenaFloorFile(void)
{
	std::ofstream file("data/arenafloor.txt");

	if (!file.is_open())
	{
		return false;
	}

	file << firstFloor << std::endl;
	file << secondFloor << std::endl;
	file << thirdFloor << std::endl;
	file << fourthFloor << std::endl;

	file.close();

	return true;
}

void Result::ArenaFloorRankUpdate(void)
{
	std::vector<int> floors;

	floors.push_back(firstFloor);
	floors.push_back(secondFloor);
	floors.push_back(thirdFloor);
	floors.push_back(fourthFloor);
	floors.push_back(arenaFloor);

	std::sort(floors.begin(), floors.end(), std::greater<int>());

	firstFloor = floors[0];
	secondFloor = floors[1];
	thirdFloor = floors[2];
	fourthFloor = floors[3];

	SaveArenaFloorFile();
}