#pragma once
#include "StDefine.h"


class HowtoPlay
{
public:

	HowtoPlay();
	~HowtoPlay();

	bool SystemInit(void);
	void GameInit(void);
	void UpDate(void);
	void Draw(void);
	bool Release(void);

	E_SCENE_ID GetNextSceneID(void) { return nextSceneID; }



private:
	E_SCENE_ID nextSceneID;

	int htpSe;


	int nowimg;

	int padimg;
	int keyimg;

};

