#pragma once
#include "Vector2.h"
#include "Vector2F.h"
#include <vector>
#include <string>

class cursor;
class PeaceBase;


class GameScene
{public:


	const int BOARD_ORIGIN_X = 560;
	const int BOARD_ORIGIN_Y = 160;
	const int CELL_SIZE = 80;

	GameScene(void);

	~GameScene(void);


	bool SystemInit(void);			//初期化処理(最初の1回のみ実行)
	void GameInit(void);			//ゲーム起動・再開時に必ず呼び出す処理
	void Update(void);				//更新処理
	void Draw(void);				//描画処理
	bool Release(void);				//解放処理(最後の１回のみ実行)

	void CollisionCheck(void);
	




	void CreateStageFromText(const std::string& text);
	PeaceBase* CreatePeaceByType(int type, int x, int y);
	void MoveRandomPiecesOutside(int count);
	void CheckFitPiece(PeaceBase* p);

	bool IsClear(void);		

private:
	cursor* Cursor;
	std::vector<PeaceBase*> peace;

	std::vector<std::string> stageList;
	std::vector<std::string> stageFileList;

	bool LoadStageFile(const std::string& filePath);
	bool LoadRandomStageFile(void);

	bool CollisionCheckRectCenter(Vector2 cPos1, Vector2 size1, Vector2 cPos2, Vector2 size2);

	bool isClear = false;
	int clearWaitFrame = 0;

	struct FitTarget
	{
		int type;
		Vector2F pos;
		bool occupied;
	};

	std::vector<FitTarget> fitTargets;

	static constexpr int CLEAR_WAIT_FRAME = 60; // 60フレーム待って次の問題へ

	void StartNewPuzzle(void);
	void ClearPieces(void);


	bool CheckClear(void);
};

