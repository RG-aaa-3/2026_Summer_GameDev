#pragma once
#include "Vector2.h"
#include <vector>

class cursor;
class PeaceBase;


class GameScene
{public:



	GameScene(void);

	~GameScene(void);


	bool SystemInit(void);			//初期化処理(最初の1回のみ実行)
	void GameInit(void);			//ゲーム起動・再開時に必ず呼び出す処理
	void Update(void);				//更新処理
	void Draw(void);				//描画処理
	bool Release(void);				//解放処理(最後の１回のみ実行)

	void CollisionCheck(void);
	

private:
	cursor* Cursor;
	std::vector<PeaceBase*> peace;

	bool CollisionCheckRectCenter(Vector2 cPos1, Vector2 size1, Vector2 cPos2, Vector2 size2);


};

