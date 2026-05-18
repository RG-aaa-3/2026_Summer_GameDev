#pragma once
#include "StDefine.h"

class GameScene;
class Fader;




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
	Fader* fader;

	void Update(void);
	void Draw(void);

	E_SCENE_ID scene_ID;			//現在のシーンID
	E_SCENE_ID waitScene;			//シーンチェンジで次に遷移するシーンのID
	bool sceneChaneFlg;				//シーンチェンジ実行中フラグ	


	//シーン遷移処理
	bool ChangeScene(E_SCENE_ID  id);
	void ReleaseScene(E_SCENE_ID id);



};

