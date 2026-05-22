#include "SceneManager.h"
#include <DxLib.h>
#include "GameScene.h"
#include "Fader.h"




SceneManager::SceneManager(void) {
	gs = nullptr;
	fader = nullptr;



	scene_ID = waitScene = E_SCENE_NON;

}

SceneManager::~SceneManager(void) {

}

void SceneManager::Run(void) {
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0){

	Update();
	Draw();

	}

}

bool SceneManager::SystemInit(void) {
	// システム処理
	SetWindowText("2516001 有迫　勇智");						// ゲームウィンドウのタイトル
	SetGraphMode(SCREEN_SIZE_WID, SCREEN_SIZE_HIG, 32);		// ゲームウィンドウのサイズと色モードを設定
	ChangeWindowMode(true);									// ゲームウィンドウの表示方法(false = フルスクリーン)

	if (DxLib_Init() == -1) {
		return false;	//初期化失敗のためエラー終了
	}



	
	//インスタンス作成
	fader = new Fader();
	if (fader == nullptr)return false;
	SetTransColor(0xff, 0x00, 0xff);//透過色の設定
	fader->SystemInit();
	sceneChaneFlg = false;
	ChangeScene(E_SCENE_GAME);
	waitScene = E_SCENE_GAME;



	return true;
}




void SceneManager::Update(void) {
#if 0


	fader->Update();
	//シーンチェンジ実行中
	//フェードアウト
	if (fader->IsEnd() && waitScene != E_SCENE_NON) {
		ChangeScene(waitScene);
		waitScene = E_SCENE_NON;
		fader->SetFade(E_STAT_FADE_IN);
	}
	//フェードイン
	else if (fader->IsEnd() && waitScene == E_SCENE_NON) {
		sceneChaneFlg = false;

	}
	else {
#endif
		E_SCENE_ID nextSceneID = scene_ID;

		//各シーンUpdate処理

		switch (scene_ID) {
		case E_SCENE_TITLE:

			break;

		case E_SCENE_MODE:

			break;
		
		case E_SCENE_GAME:
			gs->Update();
			nextSceneID = gs->GetNextSceneID();

			break;

		case E_SCENE_RESULT:

			break;

		}

		//シーン遷移判定
		if (scene_ID != nextSceneID) {
			sceneChaneFlg = true;
			waitScene = nextSceneID;
			fader->SetFade(E_STAT_FADE_OUT);
		}

	}

	




void SceneManager::Draw(void) {
	//同上
	SetDrawScreen(DX_SCREEN_BACK);			// 描画する画面を裏の画面に設定する
	ClearDrawScreen();						// 描画する画面の内容を消去する

	switch (scene_ID) {
	case E_SCENE_TITLE:

		break;

	case E_SCENE_MODE:

		break;

	case E_SCENE_GAME:
		gs->Draw();
		break;

	case E_SCENE_RESULT:

		break;

	}
	fader->Draw();



	ScreenFlip();
}



bool SceneManager::Release(void) {

	ReleaseScene(E_SCENE_TITLE);
	ReleaseScene(E_SCENE_MODE);
	ReleaseScene(E_SCENE_GAME);
	ReleaseScene(E_SCENE_RESULT);

	fader->Release();
	delete fader;
	fader = nullptr;


	return true;
}




bool SceneManager::ChangeScene(E_SCENE_ID id) {
	//現在のシーンを開放
	ReleaseScene(scene_ID);

	//シーンIDを変更
	scene_ID = id;
	switch (scene_ID) {
	case E_SCENE_TITLE:

		break;

	case E_SCENE_MODE:

		break;

	case E_SCENE_GAME:
		if (gs == nullptr) {
			gs = new GameScene();
			if (gs == nullptr)return false;
			gs->SystemInit();
			gs->GameInit();

		}
		break;

	case E_SCENE_RESULT:

		break;

	}
	return true;
}




void SceneManager::ReleaseScene(E_SCENE_ID id) {



	switch (scene_ID) {
	case E_SCENE_TITLE:

		break;

	case E_SCENE_MODE:

		break;

	case E_SCENE_GAME:
		if (gs != nullptr) {
			gs->Release();
			delete gs;
			gs = nullptr;
		}
		break;

	case E_SCENE_RESULT:

		break;

	}


}