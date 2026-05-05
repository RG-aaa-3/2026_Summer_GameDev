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

	Vector2 pPos;
	DrawExtendGraph(pPos.x - size.x / 2, pPos.y - size.y / 2,
		size.x / wide, size.y / wide, peace_img[peaceDir], true);

}

bool PeaceBase::Release(void) {

	return true;
}


