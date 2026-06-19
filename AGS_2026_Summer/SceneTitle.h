#pragma once
#include "StDefine.h"




class TitleScene
{
public:

	static constexpr int TITLE_SIZE_WID = 1920;
	static constexpr int TITLE_SIZE_HIG = 1080;

	TitleScene(void);
	~TitleScene(void);

	bool SystemInit(void);
	void GameInit(void);
	void UpDate(void);
	void Draw(void);
	bool Release(void);

	E_SCENE_ID GetNextSceneID(void) { return nextSceneID; }

	void GameQuitkakunin(void);		//ゲーム終了確認
	void GameQuitkakuninDraw();



private:
	
	bool nowRightButton, prevRightButton = false;


	//確認画像
	int yesimg;
	int noimg;

	int imgtrg = 1;

	bool Quitkakunin = false;

	E_SCENE_ID nextSceneID;
	int prevSpaceKey, nowSpaceKey;

	int imgTi;   
};

