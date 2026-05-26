#include "SceneManager.h"
#include <DxLib.h>
#include "GameScene.h"
#include "Fader.h"
#include "Result.h"
#include "SceneTitle.h"


SceneManager::SceneManager(void) {
	gs = nullptr;
	fader = nullptr;
	rs = nullptr;
	title = nullptr;


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
	ChangeWindowMode(false);									// ゲームウィンドウの表示方法(false = フルスクリーン)

	if (DxLib_Init() == -1) {
		return false;	//初期化失敗のためエラー終了
	}



	
	//インスタンス作成
	fader = new Fader();
	if (fader == nullptr)return false;

	fader->SystemInit();
	sceneChaneFlg = false;
	ChangeScene(E_SCENE_TITLE);
	waitScene = E_SCENE_TITLE;



	return true;
}




void SceneManager::Update(void)
{
	fader->Update();

	// フェードアウトが終わったら、待機中のシーンへ切り替え
	if (fader->IsEnd() && waitScene != E_SCENE_NON)
	{
		ChangeScene(waitScene);
		waitScene = E_SCENE_NON;
		fader->SetFade(E_STAT_FADE_IN);
		return;
	}

	// フェード中は現在シーンのUpdateを止める
	if (!fader->IsEnd())
	{
		return;
	}

	// ここから通常時のシーン更新
	E_SCENE_ID nextSceneID = scene_ID;

	switch (scene_ID)
	{
	case E_SCENE_TITLE:
		if (title != nullptr) {
			title->UpDate();
			nextSceneID = title->GetNextSceneID();
		}
		break;

	case E_SCENE_MODE:
		break;

	case E_SCENE_GAME:
		if (gs != nullptr)
		{
			gs->Update();
			nextSceneID = gs->GetNextSceneID();
		}
		break;

	case E_SCENE_RESULT:
		if (rs != nullptr)
		{
			rs->Update();
			nextSceneID = rs->GetNextSceneID();
		}
		break;
	}

	if (scene_ID != nextSceneID) {

		if (scene_ID == E_SCENE_GAME && nextSceneID == E_SCENE_RESULT) {
			if (gs != nullptr) {
				resultScore = gs->GetScore();
			}
		}

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
		title->Draw();
		break;

	case E_SCENE_MODE:

		break;

	case E_SCENE_GAME:
		gs->Draw();
		break;

	case E_SCENE_RESULT:
		rs->Draw();
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
		if (title == nullptr)
		{
			title = new TitleScene();
			if (title == nullptr)return false;
			title->SystemInit();
			title->GameInit();

		}
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
		if (rs == nullptr) {
			rs = new Result();
			if (rs == nullptr) return false;

			rs->SystemInit();
			rs->SetScore(resultScore);
			rs->GameInit();
		}

		break;

	}
	return true;
}




void SceneManager::ReleaseScene(E_SCENE_ID id) {



	switch (id) {
	case E_SCENE_TITLE:
		if (title != nullptr) {
			title->Release();
			delete title;
			title = nullptr;
		}
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
		if (rs != nullptr) {
			rs->Release();
			delete rs;
			rs = nullptr;
		}
		break;

	}


}