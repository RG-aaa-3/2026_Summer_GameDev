#pragma once
#include "GameScene.h"
#include "SceneTitle.h"
#include "SceneSelect.h"

class TitleScene;


class SceneManager
{public:

	static constexpr int SCREEN_SIZE_WID = 1920;
	static constexpr int SCREEN_SIZE_HIG = 1080;


	SceneManager(void);			//コンストラクタ
	~SceneManager(void);		//デストラクタ

	void Run(void);				//ゲームのメイン関数
	bool SystemInit(void);			//初期化処理(最初の１回のみ実行)
	bool Release(void);				//開放処理(最後の１回のみ実行)




private:
	GameScene* gs;
	TitleScene* Ti;
	SceneSelect* Se;

	bool SceneChangeFlg;

	bool ChangeScene(E_SCENE_ID id);
	

	void Update(void);
	void Draw(void);


};

