#pragma once
#include "StDefine.h"


class ModeSelect
{
public:

	static constexpr int MODESELECT_PICTURE_HIG =267;
	static constexpr int MODESELECT_PICTURE_WID = 189;



	ModeSelect();
	~ModeSelect();


	bool SystemInit(void);			//初期化処理(最初の1回のみ実行)
	void GameInit(void);			//ゲーム起動・再開時に必ず呼び出す処理
	void Update(void);				//更新処理
	void Draw(void);				//描画処理
	bool Release(void);				//解放処理(最後の１回のみ実行)

	void ChangeDiffPicture(void);
	void ChangeModePicture(void);
	void BoarderTextUpdate(void);

	void Input(void);	//左右操作でモード切替、上下操作で難易度変更
	void SubmitGame(void);

	int GetBorderPoint(void);

	void GameQuitkakunin(void);		//ゲーム終了確認
	void GameQuitkakuninDraw();

	E_SCENE_ID GetNextSceneID(void) { return nextSceneID; }

	E_GAME_MODE_ID GetModeId(void) const { return modeId; }

	E_GAME_DIFF_ID GetDiffId(void) const { return diffId; }
private:


	//難易度選択画像のハンドル
	int lv1img;
	int lv2img;
	int lv3img;

	int haikei;		//背景

	//確認画像
	int yesimg;
	int noimg;

	int imgtrg = 1;

	//難易度ごとのクリアポイント
	int Easy = 100;
	int Hard = 200;
	int Master = 400;


	int Texttime;

	int x;
	int y;

	int textx;
	int texty;

	int nowSpaceKey;
	int prevSpaceKey;

	int nowKeyInputU;
	int nowKeyInputD;
	int nowKeyInputR;
	int nowKeyInputL;

	int prevKeyInputU;
	int prevKeyInputD;
	int prevKeyInputR;
	int prevKeyInputL;

	bool Quitkakunin = false;

	E_GAME_MODE_ID modeId;

	E_GAME_DIFF_ID diffId;


	E_SCENE_ID nextSceneID;
};

