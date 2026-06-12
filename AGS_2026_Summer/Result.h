#pragma once
#include "StDefine.h"


class GameScene;

class ModeSelect;

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



	void SetScore(int score);



	void SetResultData(int score, int border);

	private:

	ModeSelect* mode;



	//リザルト画面のハンドル**

	int result;



	E_SCENE_ID nextSceneID;

	int prevNextKey, nowNextKey;



	 int firstscore;

	int secondscore;

	int thirdscore;

	 int fourcescore;

	int myscore;

	int prevscore;



	bool clear;

	int borderPoint = 0;



	bool LoadHighScoreFile(void);

	 bool SaveHighScoreFile(void);



};

