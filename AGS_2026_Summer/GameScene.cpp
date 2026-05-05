#include "GameScene.h"
#include <DxLib.h>
#include "cursor.h"
#include "Vector2F.h"
#include "PeaceBase.h"

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


	size_t size = peace.size();
	std::vector<PeaceBase*>::iterator eitr = peace.begin();
	for (int ii = 0; ii < size; ii++) {
		(*eitr)->Update();
		eitr++;
	}
	CollisionCheck();


	Cursor->Update();


}

void GameScene::Draw(void) {
	Cursor->Draw();

	size_t size = peace.size();
	std::vector<PeaceBase*>::iterator eitr = peace.begin();
	for (int ii = 0; ii < size; ii++) {
		(*eitr)->Draw();
		eitr++;

	}




}

bool GameScene::Release(void) {
	Cursor->Release();
	delete Cursor;
	Cursor = nullptr;

	return true;
}


void GameScene::CollisionCheck(void) {
	//カーソルの位置
	Vector2F pos = Cursor->GetCursorPos();
	Vector2 cPos = AsoUtility::Round(pos);
	Vector2 cSize = { cursor::CURSOR_IMG_WID,cursor::CURSOR_IMG_HIG };

	//ピースの数だけチェック
	size_t size = peace.size();
	for (int ii = 0; ii < size; ii++) {
		pos = peace[ii]->GetPeacePos();

		Vector2 pPos = AsoUtility::Round(pos);
		Vector2 pSize = peace[ii]->GetPeaceSize();

		//カーソルとピースが触れているか
		if (CollisionCheckRectCenter(cPos, cSize, pPos, pSize)){
			Cursor->CanHold(1);		//掴める
		}
		else {
			Cursor->CanHold(2);
		}


	}

}

bool GameScene::CollisionCheckRectCenter(Vector2 cPos1, Vector2 size1, Vector2 cPos2, Vector2 size2) {

	//1つ目の湛慶の座標を求める
	Vector2 stPos1 = cPos1;
	Vector2 edPos1 = cPos1;

	stPos1.x -= (size1.x / 2);
	stPos1.y -= (size1.y / 2);
	edPos1.x += (size1.x / 2);
	edPos1.y += (size1.y / 2);

	//2つ目
	Vector2 stPos2 = cPos2;
	Vector2 edPos2 = cPos2;

	stPos2.x -= (size2.x / 2);
	stPos2.y -= (size2.y / 2);
	edPos2.x += (size2.x / 2);
	edPos2.y += (size2.y / 2);


	if (stPos1.x<edPos2.x &&
		edPos1.x>stPos2.x &&
		stPos1.y<edPos2.y &&
		edPos1.y>stPos2.y) {
		return true;
	}
	return false;
}

