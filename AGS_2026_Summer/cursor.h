#pragma once
#include "Vector2.h"
class cursor
{public:

	~cursor(void);
	cursor(void);


	static constexpr int CURSOR_IMG_HIG = 48;	//カーソルアイコンの高さサイズ
	static constexpr int CURSOR_IMG_WID = 48;	//カーソルアイコンの幅サイズ

	static constexpr int CURSOR_MOVE_SPEED_X = 2;
	static constexpr int CURSOR_MOVE_SPEED_Y = 2;




	bool SystemInit(void);			//初期化処理(最初の1回のみ実行)
	void GameInit(void);			//ゲーム起動・再開時に必ず呼び出す処理
	void Update(void);				//更新処理
	void Draw(void);				//描画処理
	bool Release(void);				//解放処理(最後の１回のみ実行)

	void Cursormove(void);



	Vector2 GetPlayerPos(void) { return pos; }


private:
	int img;
	Vector2 pos;
	bool holdflg;		//ピースをつかんでいるか(true=つかんでいる)

};

