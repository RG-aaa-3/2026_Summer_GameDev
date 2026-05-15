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



	//持っていないピースを描画
	for (int i = 0; i < peace.size(); i++)
	{
		if (peace[i] == nullptr) continue;

		if (peace[i]->IsHolding() == false)
		{
			peace[i]->Draw();
		}
	}

	// 持っているピースを描画
	for (int i = 0; i < peace.size(); i++)
	{
		if (peace[i] == nullptr) continue;

		if (peace[i]->IsHolding() == true)
		{
			peace[i]->Draw();
		}
	}

	// カーソルは最後
	Cursor->Draw();

	if (isClear)
	{
		DrawString(
			850,
			450,
			"CLEAR!",
			GetColor(255, 255, 0)
		);
	}

}



bool GameScene::Release(void) {

	Cursor->Release();
	delete Cursor;
	Cursor = nullptr;



	return true;
}





bool GameScene::CollisionCheckRectCenter(Vector2 cPos1, Vector2 size1, Vector2 cPos2, Vector2 size2) {

	//1つ目の座標を求める
	Vector2 stPos1 = cPos1;
	Vector2 edPos1 = cPos1;

	stPos1.x -= (size1.x / 2);
	stPos1.y -= (size1.y / 2);
	edPos1.x += (size1.x / 2);
	edPos1.y += (size1.y / 2);

	//2つ目
	Vector2 stPos2 = cPos2;
	Vector2 edPos2 = cPos2;

	stPos2.x -= (size2.x / 2);
	stPos2.y -= (size2.y / 2);
	edPos2.x += (size2.x / 2);
	edPos2.y += (size2.y / 2);


	if (stPos1.x<edPos2.x &&
		edPos1.x>stPos2.x &&
		stPos1.y<edPos2.y &&
		edPos1.y>stPos2.y) {
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

	// "/" で行を分ける
	while (std::getline(rowStream, rowText, '/'))
	{
		std::stringstream colStream(rowText);
		std::string cell;

		int col = 0;

		// "," で列を分ける
		while (std::getline(colStream, cell, ','))
		{
			// 空白マス
			if (cell.empty() || cell == "0")
			{
				col++;
				continue;
			}

			int type = std::atoi(cell.c_str());

			int x = BOARD_ORIGIN_X + col * CELL_SIZE;
			int y = BOARD_ORIGIN_Y + row * CELL_SIZE;

			Vector2F correctPos((float)x, (float)y);

			// 正解スロットを作る
			FitTarget target;
			target.type = type;
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
				p->SetTargetIndex(targetIndex);

				p->SetPeacePos(correctPos);
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
			{1, 1},
			{1, 1}
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
			{1},
			{1},
			{1},
			{1}
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
			{0,1,1},
			{1,1,0}
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
			{1,1,0},
			{0,1,1}
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
			{0,1},
			{0,1},
			{1,1}
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
			{1,0},
			{1,0},
			{1,1}
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
			{1,1,1},
			{0,1,0}
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

		Vector2F outPos;
		outPos.x = 500.0f + moved * 100.0f;
		outPos.y = 600.0f;

		p->SetPeacePos(outPos);
		p->SetPlaced(false);

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

	Vector2F pieceCenter = p->GetCenterPos();
	Vector2 currentSize = p->GetCurrentPeaceSize();

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

		Vector2F targetCenter;
		targetCenter.x = fitTargets[i].pos.x + currentSize.x / 2.0f;
		targetCenter.y = fitTargets[i].pos.y + currentSize.y / 2.0f;

		float dx = pieceCenter.x - targetCenter.x;
		float dy = pieceCenter.y - targetCenter.y;

		float distSq = dx * dx + dy * dy;

		if (distSq < bestDistSq)
		{
			bestDistSq = distSq;
			bestIndex = i;
		}
	}

	if (bestIndex != -1)
	{
		p->SetPeacePos(fitTargets[bestIndex].pos);
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

	CreateStageFromText(stageList[index]);


	//問題ごとにランダムに指定
	int Outsideamount = 1 + GetRand(5);


	// 外に出すピース数
	MoveRandomPiecesOutside(Outsideamount);
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

		stageList.push_back(line);
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
