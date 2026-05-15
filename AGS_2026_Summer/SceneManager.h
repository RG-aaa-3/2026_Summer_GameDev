#pragma once
#include "GameScene.h"

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


	void Update(void);
	void Draw(void);


};

