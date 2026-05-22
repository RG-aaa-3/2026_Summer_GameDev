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

 void PeaceBase::Update(
	 const Vector2F& cursorPos,
	 bool holdButton,
	 bool rotateLeftButton,
	 bool rotateRightButton
 )
 {
	 releasedThisFrame = false;

	 bool triggerHold = holdButton && !prevHoldButton;
	 bool triggerRelease = !holdButton && prevHoldButton;

	 bool triggerRotateLeft = rotateLeftButton && !prevRotateLeftButton;
	 bool triggerRotateRight = rotateRightButton && !prevRotateRightButton;

	 if (isPlaced)
	 {
		 prevHoldButton = holdButton;
		 prevRotateLeftButton = rotateLeftButton;
		 prevRotateRightButton = rotateRightButton;
		 return;
	 }

	 // 掴み始め
	 if (triggerHold && !isHolding)
	 {
		 if (IsCursorOnPiece(cursorPos))
		 {
			 isHolding = true;

			 dragOffset.x = cursorPos.x - peacePos.x;
			 dragOffset.y = cursorPos.y - peacePos.y;
		 }
	 }

	 // 掴んでいる間
	 if (isHolding)
	 {
		 peacePos.x = cursorPos.x - dragOffset.x;
		 peacePos.y = cursorPos.y - dragOffset.y;

		 // Vで左回転
		 if (triggerRotateLeft)
		 {
			 peaceDir--;

			 if (peaceDir < 0)
			 {
				 peaceDir = 3;
			 }
		 }

		 // Nで右回転
		 if (triggerRotateRight)
		 {
			 peaceDir++;

			 if (peaceDir > 3)
			 {
				 peaceDir = 0;
			 }
		 }
	 }

	 // 離した瞬間
	 if (triggerRelease && isHolding)
	 {
		 isHolding = false;
		 releasedThisFrame = true;
	 }

	 prevHoldButton = holdButton;
	 prevRotateLeftButton = rotateLeftButton;
	 prevRotateRightButton = rotateRightButton;
 }


 void PeaceBase::Draw(void)
 {
	 Vector2 drawSize = GetDrawSize();

	 double angle = 0.0;

	 switch (peaceDir)
	 {
	 case 0: angle = 0.0; break;
	 case 1: angle = DX_PI / 2.0; break;
	 case 2: angle = DX_PI; break;
	 case 3: angle = DX_PI * 3.0 / 2.0; break;
	 }

	 float centerX = peacePos.x + drawSize.x / 2.0f;
	 float centerY = peacePos.y + drawSize.y / 2.0f;

	 double scale = (double)drawSize.x / (double)size.x;

	 DrawRotaGraph(
		 (int)centerX,
		 (int)centerY,
		 scale,
		 angle,
		 peace_img[0],
		 true
	 );
#if 0
	 // デバッグ赤枠
	 DrawBox(
		 (int)peacePos.x,
		 (int)peacePos.y,
		 (int)(peacePos.x + drawSize.x),
		 (int)(peacePos.y + drawSize.y),
		 GetColor(255, 0, 0),
		 false
	 );
#endif
 }

 bool PeaceBase::IsCursorOnPiece(const Vector2F& cursorPos)
 {
	 Vector2 drawSize = GetDrawSize();

	 float left = peacePos.x;
	 float top = peacePos.y;
	 float right = peacePos.x + drawSize.x;
	 float bottom = peacePos.y + drawSize.y;

	 return
		 cursorPos.x >= left &&
		 cursorPos.x <= right &&
		 cursorPos.y >= top &&
		 cursorPos.y <= bottom;
 }

Vector2 PeaceBase::GetCurrentPeaceSize(void) const
{
	if (shape.empty())
	{
		return Vector2(0, 0);
	}

	int baseW = (int)shape[0].size() * cellSize;
	int baseH = (int)shape.size() * cellSize;

	// 0度・180度
	if (peaceDir % 2 == 0)
	{
		return Vector2(baseW, baseH);
	}

	// 90度・270度は横幅と高さが入れ替わる
	return Vector2(baseH, baseW);
}


Vector2F PeaceBase::GetCenterPos(void) const
{
	Vector2 size = GetCurrentPeaceSize();

	return Vector2F(
		peacePos.x + size.x / 2.0f,
		peacePos.y + size.y / 2.0f
	);
}

std::vector<std::vector<int>> PeaceBase::GetCanvasShape(void) const
{
	const int CANVAS = 4;

	std::vector<std::vector<int>> canvas(
		CANVAS,
		std::vector<int>(CANVAS, 0)
	);

	for (int y = 0; y < shape.size(); y++)
	{
		for (int x = 0; x < shape[y].size(); x++)
		{
			if (y >= CANVAS || x >= CANVAS) continue;

			canvas[y][x] = shape[y][x];
		}
	}

	return canvas;
}


std::vector<std::vector<int>> PeaceBase::RotateShapeRight(
	const std::vector<std::vector<int>>& src
) const
{
	int h = (int)src.size();
	int w = (int)src[0].size();

	std::vector<std::vector<int>> dst(
		w,
		std::vector<int>(h, 0)
	);

	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			dst[x][h - 1 - y] = src[y][x];
		}
	}

	return dst;
}


std::vector<std::vector<int>> PeaceBase::GetRotatedCanvasShape(void) const
{
	std::vector<std::vector<int>> result = GetCanvasShape();

	int rotateCount = peaceDir % 4;

	for (int i = 0; i < rotateCount; i++)
	{
		result = RotateShapeRight(result);
	}

	return result;
}


Vector2F PeaceBase::GetJudgeOffset(void) const
{
	std::vector<std::vector<int>> rotated = GetRotatedCanvasShape();

	int minX = 999;
	int minY = 999;

	for (int y = 0; y < rotated.size(); y++)
	{
		for (int x = 0; x < rotated[y].size(); x++)
		{
			if (rotated[y][x] == 0) continue;

			if (x < minX) minX = x;
			if (y < minY) minY = y;
		}
	}

	if (minX == 999 || minY == 999)
	{
		return Vector2F(0.0f, 0.0f);
	}

	Vector2F offset(
		(float)(minX * cellSize),
		(float)(minY * cellSize)
	);

	if (peaceType == 9 && peaceDir == 9)
	{
		offset.y += cellSize;
	}

	return offset;
}

Vector2F PeaceBase::GetJudgePos(void) const
{
	Vector2F offset = GetJudgeOffset();

	return Vector2F(
		peacePos.x + offset.x,
		peacePos.y + offset.y
	);
}

Vector2 PeaceBase::GetDrawSize(void) const
{
	Vector2 drawSize;

	drawSize.x = size.x / wide;
	drawSize.y = size.y / wide;

	return drawSize;
}

Vector2F PeaceBase::GetBodyPos(void) const
{
	Vector2F offset = GetJudgeOffset();

	return Vector2F(
		peacePos.x + offset.x,
		peacePos.y + offset.y
	);
}

void PeaceBase::SetBodyPos(const Vector2F& bodyPos)
{
	Vector2F offset = GetJudgeOffset();

	peacePos.x = bodyPos.x - offset.x;
	peacePos.y = bodyPos.y - offset.y;
}