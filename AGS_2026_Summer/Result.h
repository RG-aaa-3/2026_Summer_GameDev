#pragma once
#include "StDefine.h"
#include <string>

class GameScene;

class ModeSelect;
class SceneManager;

class SceneManager;



class Result

{

public:



	Result(void);



	~Result(void);





	bool SystemInit(void);			//初期化処理(最初の1回のみ実行)

	 void GameInit(void);			//ゲーム起動・再開時に必ず呼び出す処理

	void Update(void);				//更新処理

	void Draw(void);				//描画処理

	bool Release(void);				//解放処理(最後の１回のみ実行)



	 void HighScoreUpdate(void);



	void IsBorderCleard(void);



	 E_SCENE_ID GetNextSceneID(void) { return nextSceneID; }

	void SetBorderPoint(int border) { borderPoint = border; }

	std::string GetHighScoreFilePath(void) const;

	void SetResultData(
		int score,
		int border,
		E_GAME_MODE_ID mode,
		E_GAME_DIFF_ID diff,
		int floor
	);

	private:

	ModeSelect* mode;

	//リザルト画面のハンドル
	int result;


	//効果音のハンドル
	int clearSe;

	int failedSe;




	E_SCENE_ID nextSceneID;

	int prevNextKey, nowNextKey;


	//スコアランキング用

	E_GAME_DIFF_ID resultDiffId = E_DIFF_EASY;


	 int firstscore;

	int secondscore;

	int thirdscore;

	 int fourcescore;

	int myscore;

	int prevscore;

	//アリーナ階層ランキング用
	E_GAME_MODE_ID resultModeId = E_MODE_BASIC;

	int arenaFloor = 0;

	int firstFloor = 0;
	int secondFloor = 0;
	int thirdFloor = 0;
	int fourthFloor = 0;

	bool LoadArenaFloorFile(void);
	bool SaveArenaFloorFile(void);
	void ArenaFloorRankUpdate(void);



	bool clear;

	int borderPoint = 0;



	bool LoadHighScoreFile(void);

	 bool SaveHighScoreFile(void);



};

