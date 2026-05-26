#pragma once
#include "StDefine.h"



class GameScene;

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

	E_SCENE_ID GetNextSceneID(void) { return nextSceneID; }

	void SetScore(int score);

private:


	E_SCENE_ID nextSceneID;
	int prevNextKey, nowNextKey;

	int firstscore;
	int secondscore;
	int thirdscore;
	int fourcescore;
	int myscore;
	int prevscore;

	bool LoadHighScoreFile(void);
	bool SaveHighScoreFile(void);

};

