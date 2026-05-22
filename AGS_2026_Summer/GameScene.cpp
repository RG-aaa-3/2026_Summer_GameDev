#include "GameScene.h"
#include <DxLib.h>
#include "cursor.h"
#include "Vector2F.h"
#include "PeaceBase.h"
#include "PeaceO.h"
#include <sstream>
#include <cstdlib>
#include <ctime>
#include "PeaceT.h"
#include "PeaceI.h"
#include "PeaceS.h"
#include "PeaceZ.h"
#include "PeaceJ.h"
#include "PeaceL.h"
#include <fstream>
#include <string>
#include <vector>




GameScene::GameScene(void) {
	Cursor = nullptr;


}

GameScene::~GameScene(void) {

}


bool GameScene::SystemInit(void)
{
	isClear = false;
	clearWaitFrame = 0;

	Cursor = new cursor();
	if (Cursor == nullptr) return false;
	if (Cursor->SystemInit() == false) return false;

	gameStartTimeMs = GetNowCount();

	// 問題ファイル一覧
	stageFileList.push_back("data/mondai1.txt");
	//stageFileList.push_back("data/mondai2.txt");
	//stageFileList.push_back("data/mondai3.txt");

	// ランダムで1つの問題ファイルを読み込む
	if (LoadRandomStageFile() == false)
	{
		return false;
	}

	StartNewPuzzle();

	return true;
}

//以下各要素呼び出し
void GameScene::GameInit(void) {
	Cursor->GameInit();


}


void GameScene::Update(void)
{

	if (IsTimeUp())
	{
		return;
	}

	if (isClear)
	{
		clearWaitFrame++;

		if (clearWaitFrame >= CLEAR_WAIT_FRAME)
		{
			StartNewPuzzle();
		}

		return;
	}



	if (isClear)
	{
		clearWaitFrame++;

		if (clearWaitFrame >= CLEAR_WAIT_FRAME)
		{
			StartNewPuzzle();
		}

		return;
	}

	Cursor->Update();

	Vector2F cursorPos = Cursor->GetPos();
	bool holdButton = CheckHitKey(KEY_INPUT_SPACE);		//スペースで掴む


	bool rotateLeftButton = CheckHitKey(KEY_INPUT_V);	//左回転
	bool rotateRightButton = CheckHitKey(KEY_INPUT_N);	//右回転

	for (int i = 0; i < peace.size(); i++)
	{
		if (peace[i] == nullptr) continue;

		peace[i]->Update(
			cursorPos,
			holdButton,
			rotateLeftButton,
			rotateRightButton
		);

		if (peace[i]->IsReleasedThisFrame())
		{
			CheckFitPiece(peace[i]);
		}
	}


	if (CheckClear())
	{
		AddClearScore();

		isClear = true;
		clearWaitFrame = 0;
	}

}

void GameScene::Draw(void) {



	//---------------------------------------------
	//デバッグ用のグリッド線
	for (int yy = 0; yy < 80 - 1; yy++) {
		DrawLine(0, 80 * (yy + 1),
			1920, 80 * (yy + 1),
			GetColor(0xff, 0xff, 0xff));
	}
	for (int xx = 0; xx < 80 - 1; xx++) {
		DrawLine(80 * (xx + 1), 0,
			80 * (xx + 1), 1080,
			GetColor(0xff, 0xff, 0xff));
	}

	for (int i = 0; i < peace.size(); i++)
	{
		if (peace[i] == nullptr) continue;
		peace[i]->Draw();
	}
	//---------------------------------------------



	for (int i = 0; i < peace.size(); i++)
	{
		if (peace[i] == nullptr) continue;

		if (peace[i]->IsHolding() == false)
		{
			peace[i]->Draw();
		}
	}

	//固定済みピースを最初に描画
	for (int i = 0; i < peace.size(); i++)
	{
		if (peace[i] == nullptr) continue;

		if (peace[i]->IsPlaced())
		{
			peace[i]->Draw();
		}
	}

	//まだ固定されていないかつ持っていないピース
	for (int i = 0; i < peace.size(); i++)
	{
		if (peace[i] == nullptr) continue;

		if (!peace[i]->IsPlaced() && !peace[i]->IsHolding())
		{
			peace[i]->Draw();
		}
	}

	//持っているピースを最後に描画    (ピースの中では最前面)
	for (int i = 0; i < peace.size(); i++)
	{
		if (peace[i] == nullptr) continue;

		if (peace[i]->IsHolding())
		{
			peace[i]->Draw();
		}
	}
	Cursor->Draw();

	float elapsed = isClear ? lastElapsedTime : GetElapsedTime();

	float remaining = GetRemainingTime();

	SetFontSize(48);

	DrawFormatString(
		1440,
		20,
		GetColor(255, 255, 255),
		"SCORE\n %d",
		totalScore
	);

	SetFontSize(24);

	DrawFormatString(
		40,
		60,
		GetColor(255, 255, 255),
		"TIME : %.2f",
		remaining
	);



	if (isClear)
	{
		DrawString(
			850,
			450,
			"CLEAR!",
			GetColor(255, 255, 0)
		);


	}

	if (IsTimeUp())
	{
		SetFontSize(64);

		DrawString(
			780,
			450,
			"TIME UP!",
			GetColor(0, 0, 0)
		);

		SetFontSize(24);
	}


}



bool GameScene::Release(void) {

	Cursor->Release();
	delete Cursor;
	Cursor = nullptr;



	return true;
}





bool GameScene::CollisionCheckRectLeftTop(Vector2 pos1, Vector2 size1, Vector2 pos2, Vector2 size2)
{
	int left1 = pos1.x;
	int top1 = pos1.y;
	int right1 = pos1.x + size1.x;
	int bottom1 = pos1.y + size1.y;

	int left2 = pos2.x;
	int top2 = pos2.y;
	int right2 = pos2.x + size2.x;
	int bottom2 = pos2.y + size2.y;

	if (left1 < right2 &&
		right1 > left2 &&
		top1 < bottom2 &&
		bottom1 > top2)
	{
		return true;
	}

	return false;
}

void GameScene::CreateStageFromText(const std::string& text)
{
	fitTargets.clear();

	std::stringstream rowStream(text);
	std::string rowText;

	int row = 0;

	while (std::getline(rowStream, rowText, '/'))
	{
		std::stringstream colStream(rowText);
		std::string cell;

		int col = 0;

		while (std::getline(colStream, cell, ','))
		{
			int type = 0;
			int dir = 0;

			// 空白マス
			if (ParseStageCell(cell, type, dir) == false)
			{
				col++;
				continue;
			}

			int x = BOARD_ORIGIN_X + col * CELL_SIZE;
			int y = BOARD_ORIGIN_Y + row * CELL_SIZE;

			Vector2F correctPos((float)x, (float)y);

			// 正解スロットを作る
			FitTarget target;
			target.type = type;
			target.dir = dir;
			target.pos = correctPos;
			target.occupied = true;

			int targetIndex = (int)fitTargets.size();
			fitTargets.push_back(target);

			// ピース生成
			PeaceBase* p = CreatePeaceByType(type, x, y);

			if (p != nullptr)
			{
				p->SetCorrectPos(correctPos);
				p->SetPeaceType(type);
				p->SetPeaceDir(dir);
				p->SetTargetIndex(targetIndex);

	
				p->SetBodyPos(correctPos);

				p->SetPlaced(true);

				peace.push_back(p);
			}

			col++;
		}

		row++;
	}
}


PeaceBase* GameScene::CreatePeaceByType(int type, int x, int y) {

	std::vector<std::vector<int>> shape;

	PeaceBase* p = nullptr;

	switch (type) {
	case 1:
		// Oミノ
		shape = {
			{1,1,0,0},
			{1,1,0,0},
			{0,0,0,0},
			{0,0,0,0}
		};

		p = new PeaceO(
			0,
			shape,
			x,
			y,
			CELL_SIZE
		);
		break;
	case 2:
		//Iミノ
		shape = {
			{1,0,0,0},
			{1,0,0,0},
			{1,0,0,0},
			{1,0,0,0}
		};

		p = new PeaceI(
			0,
			shape,
			x,
			y,
			CELL_SIZE
		);
		break;
	case 3:
		//Sミノ
		shape = {
			{0,0,1,1},
			{0,1,1,0},
			{0,0,0,0},
			{0,0,0,0}
		};

		p = new PeaceS(
			0,
			shape,
			x,
			y,
			CELL_SIZE
		);
		break;
	case 4:
		//Zミノ
		shape = {
			{1,1,0,0},
			{0,1,1,0},
			{0,0,0,0},
			{0,0,0,0}
		};

		p = new PeaceZ(
			0,
			shape,
			x,
			y,
			CELL_SIZE
		);
		break;
	case 5:
		//Jミノ
		shape = {
			{0,0,0,1},
			{0,0,0,1},
			{0,0,1,1},
			{0,0,0,0}
		};


		p = new PeaceJ(
			0,
			shape,
			x,
			y,
			CELL_SIZE
		);
		break;
	case 6:
		//Lミノ
		shape = {
			{1,0,0,0},
			{1,0,0,0},
			{1,1,0,0},
			{0,0,0,0}
		};


		p = new PeaceL(
			0,
			shape,
			x,
			y,
			CELL_SIZE
		);
		break;
	case 7:
		//Tミノ
		shape = {
			{1,1,1,0},
			{0,1,0,0},
			{0,0,0,0},
			{0,0,0,0}
		};


		p = new PeaceT(
			0,
			shape,
			x,
			y,
			CELL_SIZE
		);
		break;

	default:
		return nullptr;
	}

	if (p == nullptr) return nullptr;

	if (p->SystemInit(this) == false) {
		delete p;
		return nullptr;
	}

	return p;
}

void GameScene::MoveRandomPiecesOutside(int count)
{
	if (peace.empty()) return;

	int moved = 0;

	while (moved < count)
	{
		int index = GetRand((int)peace.size() - 1);

		PeaceBase* p = peace[index];

		if (p == nullptr) continue;
		if (p->IsPlaced() == false) continue;

		int targetIndex = p->GetTargetIndex();

		if (targetIndex >= 0 && targetIndex < fitTargets.size())
		{
			fitTargets[targetIndex].occupied = false;
		}

		p->SetTargetIndex(-1);
		p->SetPlaced(false);

		// ここで外に出したピースの向きをランダムにする
		int randomDir = GetRand(3); // 0,1,2,3
		p->SetPeaceDir(randomDir);

		Vector2F outPos;
		outPos.x = 500.0f + moved * 100.0f;
		outPos.y = 760.0f;

		// 画像キャンバスではなく、ミノ本体をこの位置に置きたい場合
		p->SetBodyPos(outPos);

		moved++;

		if (moved >= peace.size())
		{
			break;
		}
	}
}

void GameScene::CheckFitPiece(PeaceBase* p)
{
	if (p == nullptr) return;
	if (p->IsPlaced()) return;


	Vector2F pos = p->GetJudgePos();

	const float fitRange = 60.0f;

	int bestIndex = -1;
	float bestDistSq = fitRange * fitRange;

	for (int i = 0; i < fitTargets.size(); i++)
	{
		if (fitTargets[i].occupied)
		{
			continue;
		}

		if (fitTargets[i].type != p->GetPeaceType())
		{
			continue;
		}

		// 正解方向と違うなら入らない
		if (!IsSameShapeDir(p->GetPeaceType(), p->GetPeaceDir(), fitTargets[i].dir))
		{
			continue;
		}

		float dx = pos.x - fitTargets[i].pos.x;
		float dy = pos.y - fitTargets[i].pos.y;

		float distSq = dx * dx + dy * dy;

		if (distSq < bestDistSq)
		{
			bestDistSq = distSq;
			bestIndex = i;
		}
	}

	if (bestIndex != -1)
	{
		p->SetBodyPos(fitTargets[bestIndex].pos);

		p->SetPlaced(true);
		p->SetTargetIndex(bestIndex);

		fitTargets[bestIndex].occupied = true;
	}
}


bool GameScene::CheckClear(void)
{
	for (int i = 0; i < peace.size(); i++)
	{
		if (peace[i] == nullptr) continue;

		if (peace[i]->IsPlaced() == false)
		{
			return false;
		}
	}

	return true;
}


void GameScene::ClearPieces(void)
{
	for (int i = 0; i < peace.size(); i++)
	{
		if (peace[i] != nullptr)
		{
			delete peace[i];
			peace[i] = nullptr;
		}
	}

	peace.clear();
	fitTargets.clear();
}


void GameScene::StartNewPuzzle(void)
{
	ClearPieces();

	isClear = false;
	clearWaitFrame = 0;

	if (stageList.empty())
	{
		return;
	}

	int index = GetRand((int)stageList.size() - 1);

	currentDifficultyBonus = stageList[index].difficultyBonus;

	CreateStageFromText(stageList[index].text);

	// 外に出すピース数
	MoveRandomPiecesOutside(2);

	// 問題開始時間を記録
	puzzleStartTimeMs = GetNowCount();

	lastAddScore = 0;
	lastElapsedTime = 0.0f;
	lastTimeBonus = 1.0f;
}

bool GameScene::LoadStageFile(const std::string& filePath)
{
	stageList.clear();

	std::ifstream file(filePath);

	if (!file.is_open())
	{
		return false;
	}

	std::string line;

	while (std::getline(file, line))
	{
		if (line.empty())
		{
			continue;
		}

		if (line[0] == '#')
		{
			continue;
		}

		StageData data;

		size_t separator = line.find('|');

		if (separator != std::string::npos)
		{
			std::string bonusText = line.substr(0, separator);
			std::string stageText = line.substr(separator + 1);

			data.difficultyBonus = std::atoi(bonusText.c_str());
			data.text = stageText;
		}
		else
		{
			// 古い形式にも対応
			data.difficultyBonus = 10;
			data.text = line;
		}

		if (data.difficultyBonus <= 0)
		{
			data.difficultyBonus = 10;
		}

		stageList.push_back(data);
	}

	file.close();

	return !stageList.empty();
}


bool GameScene::LoadRandomStageFile(void)
{
	if (stageFileList.empty())
	{
		return false;
	}

	int index = GetRand((int)stageFileList.size() - 1);

	return LoadStageFile(stageFileList[index]);
}


float GameScene::GetElapsedTime(void) const
{
	int now = GetNowCount();
	return (now - puzzleStartTimeMs) / 1000.0f;
}


float GameScene::CalcTimeBonus(float elapsedTime) const
{
	float timeBonus = 2.0f * (10.0f - elapsedTime);

	if (timeBonus < 1.0f)
	{
		timeBonus = 1.0f;
	}

	return timeBonus;
}


int GameScene::CalcAddScore(float elapsedTime) const
{
	float timeBonus = CalcTimeBonus(elapsedTime);

	float score = currentDifficultyBonus * timeBonus;

	// 小数を四捨五入して整数スコアにする
	return (int)(score + 0.5f);
}

void GameScene::AddClearScore(void)
{
	lastElapsedTime = GetElapsedTime();
	lastTimeBonus = CalcTimeBonus(lastElapsedTime);

	lastAddScore = CalcAddScore(lastElapsedTime);
	totalScore += lastAddScore;
}

float GameScene::GetGameElapsedTime(void) const
{
	int now = GetNowCount();
	return (now - gameStartTimeMs) / 1000.0f;
}

float GameScene::GetRemainingTime(void) const
{
	float remaining = GAME_LIMIT_TIME - GetGameElapsedTime();

	if (remaining < 0.0f)
	{
		remaining = 0.0f;
	}

	return remaining;
}

bool GameScene::IsTimeUp(void) const
{
	return GetRemainingTime() <= 0.0f;
}


bool GameScene::ParseStageCell(const std::string& cell, int& type, int& dir)
{
	type = 0;

	// 指定なしなら上向き
	dir = 0;

	if (cell.empty() || cell == "0")
	{
		return false;
	}

	// [2]7 のような形式
	if (cell[0] == '[')
	{
		size_t closePos = cell.find(']');

		if (closePos == std::string::npos)
		{
			return false;
		}

		std::string dirText = cell.substr(1, closePos - 1);
		std::string typeText = cell.substr(closePos + 1);

		int dirNo = std::atoi(dirText.c_str());
		type = std::atoi(typeText.c_str());

		// 1=上, 2=右, 3=下, 4=左
		if (dirNo < 1 || dirNo > 4)
		{
			dirNo = 1;
		}

		dir = dirNo - 1;

		return type != 0;
	}

	// 古い形式：1,2,3 など
	type = std::atoi(cell.c_str());
	dir = 0;

	return type != 0;
}

bool GameScene::IsSameShapeDir(int type, int dirA, int dirB)
{
	dirA = dirA % 4;
	dirB = dirB % 4;

	switch (type)
	{
	case 1:
		// Oミノ：全方向同じ
		return true;

	case 2:
		// Iミノ：上=下、右=左
		return (dirA % 2) == (dirB % 2);

	case 3:
		// Sミノ：上=下、右=左
		return (dirA % 2) == (dirB % 2);

	case 4:
		// Zミノ：上=下、右=左
		return (dirA % 2) == (dirB % 2);

	case 5:
		// Jミノ：4方向すべて別
		return dirA == dirB;

	case 6:
		// Lミノ：4方向すべて別
		return dirA == dirB;

	case 7:
		// Tミノ：基本は4方向すべて別
		return dirA == dirB;

	default:
		return dirA == dirB;
	}
}