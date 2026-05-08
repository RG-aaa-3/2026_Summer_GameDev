#include "PeaceBase.h"
#include  <DxLib.h>
#include "cursor.h"
#include "GameScene.h"


PeaceBase::~PeaceBase() {


}

PeaceBase::PeaceBase(
	int graphHandle,
	const std::vector<std::vector<int>>& shape,
	int startX,
	int startY,
	int cellSize
)
{
	this->graphHandle = graphHandle;
	this->shape = shape;

	this->x = startX;
	this->y = startY;
	this->cellSize = cellSize;

	this->peacePos = Vector2F((float)startX, (float)startY);

	this->peaceDir = 0;
	this->wide = 1;

	for (int i = 0; i < static_cast<int>(AsoUtility::DIRECTION::E_DIR_MAX); i++) {
		peace_img[i] = -1;
	}
}


bool PeaceBase::SystemInit(GameScene* gs) {

	gInst = gs;

	SetPeacePram();

	std::string path = "image/";
	path += imgFName;

	peace_img[0] = LoadGraph(path.c_str());

	if (peace_img[0] == -1) return false;

	peaceDir = 0;

	return true;
}

 void PeaceBase::GameInit(void) {


}

 void PeaceBase::Update(const Vector2F& cursorPos, bool holdButton, bool rotateButton) {

	 bool triggerHold = holdButton && !prevHoldButton;

	 // ’Í‚ÝŽn‚ß
	 if (triggerHold && !isHolding) {

		 int drawW = size.x / wide;
		 int drawH = size.y / wide;

		 bool isCursorOnPiece =
			 cursorPos.x >= peacePos.x &&
			 cursorPos.x <= peacePos.x + drawW &&
			 cursorPos.y >= peacePos.y &&
			 cursorPos.y <= peacePos.y + drawH;

		 if (isCursorOnPiece) {
			 isHolding = true;

			 holdOffset.x = cursorPos.x - peacePos.x;
			 holdOffset.y = cursorPos.y - peacePos.y;
		 }
	 }

	 // ’Í‚ñ‚Å‚¢‚éŠÔ
	 if (isHolding) {
		 peacePos.x = cursorPos.x - holdOffset.x;
		 peacePos.y = cursorPos.y - holdOffset.y;
	 }

	 // —£‚µ‚½‚ç‰ðœ
	 if (!holdButton) {
		 isHolding = false;
	 }

	 prevHoldButton = holdButton;
	 prevRotateButton = rotateButton;
 }

void PeaceBase::Draw(void) {

	int drawW = size.x / wide;
	int drawH = size.y / wide;

	DrawExtendGraph(
		(int)peacePos.x,
		(int)peacePos.y,
		(int)peacePos.x + drawW,
		(int)peacePos.y + drawH,
		peace_img[peaceDir],
		true
	);
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