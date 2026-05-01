#include "GameScene.h"
#include <DxLib.h>
#include "cursor.h"


GameScene::GameScene(void) {
	Cursor = nullptr;


}

GameScene::~GameScene(void) {

}


bool GameScene::SystemInit(void) {
	//ポインタの初期化&チェック
	Cursor = new cursor();
	if (Cursor == nullptr)return false;
	if (Cursor->SystemInit() == false)return false;


}
//以下各要素呼び出し
void GameScene::GameInit(void) {
	Cursor->GameInit();


}

void GameScene::Update(void) {
	Cursor->Update();


}

void GameScene::Draw(void) {
	Cursor->Draw();



}

bool GameScene::Release(void) {
	Cursor->Release();
	delete Cursor;
	Cursor = nullptr;

	return true;
}
