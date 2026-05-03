#pragma once
#include <string>
#include "Vector2.h"
#include "AsoUtility.h"
#include "Vector2F.h"

class GameScene;


class PeaceBase
{
public:

	enum class PEACE_TYPE {

		PEACE_O,
		PEACE_Z,
		PEACE_S,
		PEACE_J,
		PEACE_L,
		PEACE_I,
		PEACE_T,


		PEACE_MAX,
	};

	~PeaceBase();
	PeaceBase();

	virtual bool SystemInit(GameScene* gs);			//初期化処理(最初の1回のみ実行)
	virtual void GameInit(void);			//ゲーム起動・再開時に必ず呼び出す処理
	virtual void Update(void);				//更新処理
	virtual void Draw(void);				//描画処理
	virtual bool Release(void);				//解放処理(最後の１回のみ実行)


	//個別のパラメータ設定処理
	virtual void SetPeacePram(void) = 0;


	//ピース座標取得
	virtual  Vector2F GetPeacePos(void) { return peacePos; }
	//画像サイズ取得
	virtual  Vector2 GetPeaceSize(void) { return size; }
	//掴めているか判定
	virtual bool GetHold(void) { return HoldFlg; }






protected:
	GameScene* gInst;

	//画像ハンドル番号テーブル
	int peace_img[static_cast<int> (AsoUtility::DIRECTION::E_DIR_MAX)];
	//座標位置
	Vector2F peacePos;
	//ピースの向き
	int peaceDir;
	//ホールドフラグ
	bool HoldFlg;


	//画像ファイル名
	std::string imgFName;

	//画像サイズ
	Vector2 size;

	//画像の向き設定
	void SetPeaceDirection(Vector2 pdir);



};

