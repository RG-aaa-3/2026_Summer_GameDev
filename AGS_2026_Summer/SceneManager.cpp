#include "SceneManager.h"
#include <DxLib.h>





SceneManager::SceneManager(void) {
	gs = nullptr;
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


	gs = new GameScene();
	if (gs == nullptr)return false;


	if (gs ->SystemInit() == false)return false;


	return true;
}




void SceneManager::Update(void) {
	//ここに各シーンのUpdateをSwitchで入れる

	gs->Update();

}

void SceneManager::Draw(void) {
	//同上
	SetDrawScreen(DX_SCREEN_BACK);			// 描画する画面を裏の画面に設定する
	ClearDrawScreen();						// 描画する画面の内容を消去する

	gs->Draw();



	ScreenFlip();
}



bool SceneManager::Release(void) {

	gs->Release();
	delete gs;
	gs = nullptr;



	return true;
}