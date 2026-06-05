#pragma once
#include "Vector2.h"
#include "Vector2F.h"
#include <vector>
#include <string>
#include "StDefine.h"

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
	
	bool IsSameShapeDir(int type, int dirA, int dirB);



	void CreateStageFromText(const std::string& text);
	PeaceBase* CreatePeaceByType(int type, int x, int y);
	void MoveRandomPiecesOutside(int count);
	void CheckFitPiece(PeaceBase* p);

	bool IsClear(void);		

	E_SCENE_ID GetNextSceneID(void) { return nextSceneID; }

	int GetScore(void) { return totalScore; }

private:


	cursor* Cursor;
	std::vector<PeaceBase*> peace;

	struct StageData
	{
		std::string text;
		int difficultyBonus;
	};

	enum class GAME_PHASE
	{
		READY,
		GO,
		PLAY
	};



	GAME_PHASE gamePhase;

	int readyImg = -1;		//Readyイメージハンドル番号
	int goImg = -1;			//Goイメージハンドル番号

	int startCountFrame = 0;

	// 後から変更しやすい表示時間
	int readyDisplayFrame = 40; // 60フレーム = 約1秒
	int goDisplayFrame = 50;

	void UpdateStartSequence(void);
	void DrawStartSequence(void);
	void BeginPlay(void);




	std::vector<StageData> stageList;

	std::vector<std::string> stageFileList;
	
	bool ParseStageCell(const std::string& cell, int& type, int& dir);

	bool LoadStageFile(const std::string& filePath);
	bool LoadRandomStageFile(void);
	bool CollisionCheckRectLeftTop(Vector2 pos1, Vector2 size1, Vector2 pos2, Vector2 size2);
	bool isClear = false;


	struct FitTarget
	{
		int type;
		int dir;
		Vector2F pos;
		bool occupied;
	};

	std::vector<FitTarget> fitTargets;

	static constexpr int CLEAR_WAIT_FRAME = 60; // 60フレーム待って次の問題へ
	int clearWaitFrame = 0;

	static constexpr int TIME_UP_WAIT_FRAME = 180;
	int timeupWaitFrame = 0;


	void StartNewPuzzle(void);
	void ClearPieces(void);


	bool CheckClear(void);

	//スコア
	int totalScore = 0;
	int lastAddScore = 0;

	int currentDifficultyBonus = 10;

	int puzzleStartTimeMs = 0;
	float lastElapsedTime = 0.0f;
	float lastTimeBonus = 1.0f;

	float GetElapsedTime(void) const;
	float CalcTimeBonus(float elapsedTime) const;
	int CalcAddScore(float elapsedTime) const;
	void AddClearScore(void);


	//制限時間

	int gameStartTimeMs = 0;

	static constexpr float GAME_LIMIT_TIME = 60.0f; // 制限時間 60秒

	float GetGameElapsedTime(void) const;
	float GetRemainingTime(void) const;
	bool IsTimeUp(void) const;


	int haikei;			//背景ハンドル番号

	E_SCENE_ID nextSceneID;

	//外枠表示
	bool hasGuideFrame = false;

	float guideLeft = 0.0f;
	float guideTop = 0.0f;
	float guideRight = 0.0f;
	float guideBottom = 0.0f;

	void ResetGuideFrame(void);
	void AddGuideFrameRect(const Vector2F& pos, const Vector2& size);
	void DrawGuideFrame(void);

};

