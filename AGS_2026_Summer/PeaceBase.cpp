#include "PeaceBase.h"
#include  <DxLib.h>
#include "cursor.h"


PeaceBase::~PeaceBase() {


}

PeaceBase::PeaceBase() {


}


bool PeaceBase::SystemInit(GameScene* gs) {

	gInst = gs;
	//敵キャラ個別のパラメータ設定処理
	SetPeacePram();

	std::string path = "image/";
	path += imgFName;
	int err = LoadGraph(path.c_str());

	if (err == -1)return false;

	return true;
}


 void PeaceBase::GameInit(void) {


}

void PeaceBase::Update(void) {


}

void PeaceBase::Draw(void) {


}

bool PeaceBase::Release(void) {


}


