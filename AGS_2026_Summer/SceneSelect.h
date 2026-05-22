#pragma once
#include "StDefine.h"

class SceneSelect
{
public:

	static constexpr int SCREEN_SIZE_WID = 1920;
	static constexpr int SCREEN_SIZE_HIG = 1080;

	SceneSelect(void);
	~SceneSelect(void);

	bool SystemInit(void);
	void GameInit(void);
	void UpDate(void);
	void Draw(void);
	bool Release(void);

	E_SCENE_ID GetNextSceneID(void) { return nextSceneID; }


private:

	E_SCENE_ID nextSceneID;

	int imgSe;


};

