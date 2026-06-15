#pragma once
#include "StDefine.h"

class GameScene;
class Fader;
class Result;
class TitleScene;
class ModeSelect;


class SceneManager
{public:



	static constexpr int SCREEN_SIZE_WID = 1920;
	static constexpr int SCREEN_SIZE_HIG = 1080;


	SceneManager(void);			//コンストラクタ
	~SceneManager(void);		//デストラクタ

	void Run(void);				//ゲームのメイン関数
	bool SystemInit(void);			//初期化処理(最初の１回のみ実行)
	bool Release(void);				//開放処理(最後の１回のみ実行)

	void GameEnd(void);		//ゲーム終了

private:
	GameScene* gs;
	Fader* fader;
	Result* rs;
	TitleScene* title;
	ModeSelect* mode;

	void Update(void);
	void Draw(void);

	E_SCENE_ID scene_ID;			//現在のシーンID
	E_SCENE_ID waitScene;			//シーンチェンジで次に遷移するシーンのID
	bool sceneChaneFlg;				//シーンチェンジ実行中フラグ	

	E_GAME_MODE_ID selectedModeId = E_MODE_BASIC;
	//シーン遷移処理
	bool ChangeScene(E_SCENE_ID  id);
	void ReleaseScene(E_SCENE_ID id);

	int resultScore = 0;

	int resultBorderPoint = 0;

	int resultArenaFloor = 0;
	E_GAME_MODE_ID resultModeId = E_MODE_BASIC;


	//ゲーム終了フラグ
	bool GameQuit = false;

};

