#include "cursor.h"
#include <DxLib.h>
#include "SceneManager.h"

cursor::~cursor(void) {
	img = -1;
}

cursor::cursor(void) {

}


bool cursor::SystemInit(void) {
	//カーソル画像読み込み
	img = LoadGraph("image/cursor.png");
	if (img == -1)return false;
	


	return true;
}

void cursor::GameInit(void) {



	canhold= false;
}

void cursor::Update(void) {

	Cursormove();

}

void cursor::Draw(void) {
	DrawGraph(pos.x, pos.y, img, true);

}

bool cursor::Release(void) {
	if (DeleteGraph(img) == -1)return false;

	return true;

}


void cursor::Cursormove(void) {
	//移動(上下左右キー)
	if (CheckHitKey(KEY_INPUT_LEFT)) {
		pos.x -= CURSOR_MOVE_SPEED_X;
	}
	if (CheckHitKey(KEY_INPUT_RIGHT)) {
		pos.x += CURSOR_MOVE_SPEED_X;
	}
	if (CheckHitKey(KEY_INPUT_UP)) {
		pos.y -= CURSOR_MOVE_SPEED_Y;
	}
	if (CheckHitKey(KEY_INPUT_DOWN)) {
		pos.y += CURSOR_MOVE_SPEED_Y;
	}

	//飛び出していないかのチェック
	if (pos.x < 0) {
		pos.x = 0;
	}
	// 右端のチェック
	if (pos.x > (SceneManager::SCREEN_SIZE_WID - CURSOR_IMG_HIG)) {
		pos.x = (SceneManager::SCREEN_SIZE_WID - CURSOR_IMG_WID);
	}
	// 上端のチェック
	if (pos.y < 0) {
		pos.y = 0;
	}
	// 下端のチェック
	if (pos.y > (SceneManager::SCREEN_SIZE_HIG - CURSOR_IMG_HIG)) {
		pos.y = (SceneManager::SCREEN_SIZE_HIG - CURSOR_IMG_WID);
	}



}


void cursor::GetClicked(void) {
	if (CheckHitKey(KEY_INPUT_SPACE)&&canhold) {
	
		



	}
}

void cursor::CanHold(int c) {
	
	if (c == 1) {
		canhold = true;
	}
	if (c == 2) {
		canhold = false;
	}
}


Vector2F cursor::GetPos(void) const {
	return pos;
}