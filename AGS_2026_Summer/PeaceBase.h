#pragma once
#include <string>
#include "Vector2.h"
#include "AsoUtility.h"
#include "Vector2F.h"
#include "cursor.h"
#include <vector>

class GameScene;
class cursor;

class PeaceBase
{
public:

	enum class PEACE_TYPE {

		PEACE_NONE = 0,

		PEACE_O = 1,
		PEACE_I = 2,
		PEACE_S = 3,
		PEACE_Z = 4,
		PEACE_J = 5,
		PEACE_L = 6,
		PEACE_T = 7,

		PEACE_MAX,
	};



	~PeaceBase();
	PeaceBase(int graphHandle,
			const std::vector<std::vector<int>>&shape,
			int startX,
			int startY,
			int cellSize);

	virtual bool SystemInit(GameScene* gs);			//初期化処理(最初の1回のみ実行)
	virtual void GameInit(void);			//ゲーム起動・再開時に必ず呼び出す処理
	virtual void Update(
						const Vector2F& cursorPos,
						bool holdButton,
						bool rotateLeftButton,
						bool rotateRightButton
									);				//更新処理
	virtual void Draw(void);				//描画処理
	//virtual bool Release(void);				//解放処理(最後の１回のみ実行)


	//個別のパラメータ設定処理
	virtual void SetPeacePram(void) = 0;
	bool IsCursorOnPiece(const Vector2F& cursorPos);

	//ピース座標取得
	virtual  Vector2F GetPeacePos(void) { return peacePos; }
	//画像サイズ取得
	virtual  Vector2 GetPeaceSize(void) { return size; }
	//掴めているか判定
	virtual bool GetHold(void) { return isHolding; }



	//正解場所判定
	void SetCorrectPos(const Vector2F& pos) { correctPos = pos; }
	Vector2F GetCorrectPos(void) const { return correctPos; }
	Vector2 GetCurrentPeaceSize(void) const;
	Vector2F GetCenterPos(void) const;

	void SetPeacePos(const Vector2F& pos) { peacePos = pos; }

	bool IsPlaced(void) const { return isPlaced; }
	void SetPlaced(bool flag) { isPlaced = flag; }

	bool IsReleasedThisFrame(void) const { return releasedThisFrame; }


	void SetPeaceType(int type) { peaceType = type; }
	int GetPeaceType(void) const { return peaceType; }

	void SetTargetIndex(int index) { targetIndex = index; }
	int GetTargetIndex(void) const { return targetIndex; }


	bool IsHolding(void) const { return isHolding; }


private:

	int graphHandle;
	std::vector<std::vector<int>> shape;
	
	int x;
	int y;

	int cellSize;

	int peaceType = 0;

	// 現在どの正解スロットに入っているか
	// -1ならどこにも入っていない
	int targetIndex = -1;


protected:
	GameScene* gInst;
	cursor* c;


	//画像ハンドル番号テーブル
	int peace_img[static_cast<int> (AsoUtility::DIRECTION::E_DIR_MAX)];
	//座標位置
	Vector2F peacePos;

	Vector2F dragOffset;



	//ピースの向き
	int peaceDir;

	bool prevRotateLeftButton = false;
	bool prevRotateRightButton = false;



	//ホールドフラグ
	bool isHolding;
	bool prevHoldButton = false;


	Vector2F holdOffset;

	//画像ファイル名
	std::string imgFName;

	//画像サイズ
	Vector2 size;

	//拡大/縮小量
	int wide;

	//画像の向き設定
	void SetPeaceDirection(Vector2 pdir);

	Vector2F correctPos;
	bool isPlaced = false;


	bool releasedThisFrame = false;

};

