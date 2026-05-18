#include "SceneManager.h"
#include <DxLib.h>
#include "Fader.h"


Fader::Fader(void) {

}


Fader::~Fader(void) {

}


bool Fader::SystemInit(void) {

	GameInit();

	return true;
}


void Fader::GameInit(void) {

	stat = E_STAT_FADE_NON;
	alpha = 0.0f;
	endFlg = true;

}


void Fader::Update(void) {
	if (endFlg)return;

	switch (stat) {
	case E_STAT_FADE_NON:
			return;
	case E_STAT_FADE_OUT:
		alpha += FADE_SPEED_APLHA;
		if (alpha > 255.0f) {
			//フェードアウト終了
			alpha = 255.0f;
			endFlg = true;
			stat = E_STAT_FADE_NON;
		}
		break;
	case E_STAT_FADE_IN:
		alpha -= FADE_SPEED_APLHA;
		if (alpha < 0) {
			//フェードイン終了
			alpha = 0.0f;
			endFlg = true;
			stat = E_STAT_FADE_NON;
		}
		break;
	default:
		return;

	}



}


void Fader::Draw(void) {

	switch (stat) {
	case E_STAT_FADE_NON:
		return;
	case E_STAT_FADE_OUT:
	case E_STAT_FADE_IN:
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)alpha);
		DrawBox(0, 0, SceneManager::SCREEN_SIZE_WID, SceneManager::SCREEN_SIZE_HIG, GetColor(0, 0, 0), true);
		
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);			//何もブレンドしない通常モードに戻す
		break;
	default:
		return;
	}


}



bool Fader::Release(void) {



	return true;
}

void Fader::SetFade(E_FADE_STAT_ID id) {

	stat = id;
	if (stat != E_STAT_FADE_NON) {
		endFlg = false;
	}


}