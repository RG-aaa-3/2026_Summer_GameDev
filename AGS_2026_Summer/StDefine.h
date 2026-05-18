#pragma once


//--------------------
//列挙型定義
//---------------------
enum E_SCENE_ID {
	E_SCENE_NON = -1,
	E_SCENE_TITLE,		//タイトル画面
	E_SCENE_MODE,		//ゲームモード選択
	E_SCENE_GAME,		//ゲームプレイ画面
	E_SCENE_RESULT,		//リザルト画面

	E_SCENE_ID_MAX,
};



//フェードの状態
enum E_FADE_STAT_ID {
	E_STAT_FADE_NON = -1,
	E_STAT_FADE_OUT,			//フェードアウト(徐々に暗転)
	E_STAT_FADE_IN,				//フェードイン(徐々に明転)

	E_STAT_FADE_MAX,
};