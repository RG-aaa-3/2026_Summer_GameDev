#pragma once


enum E_SCENE_ID {
	E_SCENE_NON = -1,
	E_SCENE_TITLE,                                      //タイトル
	E_SCENE_SELECT,                                     //セレクト
	E_SCENE_GAME,                                       //ゲーム画面

	E_SCENE_ID_MAX,



};

enum E_FADE_STAT_ID {

	E_STAT_FADE_NON = -1,
	E_STAT_FADE_OUT,                        // フェードアウト(徐々に暗転する)
	E_STAT_FADE_IN,                         // フェードイン(徐々に明転する)

	E_STAT_FADE_MAX,

};