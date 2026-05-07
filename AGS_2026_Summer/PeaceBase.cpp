#include "PeaceBase.h"
#include  <DxLib.h>
#include "cursor.h"
#include "GameScene.h"


PeaceBase::~PeaceBase() {


}

PeaceBase::PeaceBase(int graphHandle,
	const std::vector<std::vector<int>>& shape,
	int startX,
	int startY,
	int cellSize)
{
	this->graphHandle;
	this->shape = shape;

	this->x = startX;
	this->y = startY;
	this->cellSize = cellSize;
	

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

void PeaceBase::Update(const Vector2F& cursorPos, bool holdButton, bool rotateButton) {
	if (c->canhold) {
		peacePos.x = cursorPos.x - dragOffset.x;
		peacePos.y = cursorPos.y - dragOffset.y;

	}


	prevHoldButton = holdButton;
	prevRotateButton = rotateButton;
}

void PeaceBase::Draw(void) {

	Vector2 pPos;
	DrawExtendGraph(pPos.x - size.x / 2, pPos.y - size.y / 2,
		size.x / wide, size.y / wide, peace_img[peaceDir], true);

}

bool PeaceBase::Release(void) {

	return true;
}


bool PeaceBase::IsCursorOnPiece(const Vector2F& cursorPos) {
	for (int row = 0; row < shape.size(); row++)
	{
		for (int col = 0; col < shape[row].size(); col++)
		{
			if (shape[row][col] == 0) continue;

			float chipX = peacePos.x + col * cellSize;
			float chipY = peacePos.y + row * cellSize;

			if (
				cursorPos.x >= chipX &&
				cursorPos.x < chipX + cellSize &&
				cursorPos.y >= chipY &&
				cursorPos.y < chipY + cellSize
				)
			{
				return true;
			}
		}
	}

	return false;



}