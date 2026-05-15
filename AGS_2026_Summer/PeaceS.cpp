#include "PeaceS.h"
#include <DxLib.h>

PeaceS::PeaceS(
	int graphHandle,
	const std::vector<std::vector<int>>& shape,
	int startX,
	int startY,
	int cellSize
)
	: PeaceBase(graphHandle, shape, startX, startY, cellSize)
{
}

void PeaceS::SetPeacePram(void) {
	// 画像ファイル名
	imgFName = "PeaceS.png";

	// 元画像サイズ
	size = { 240, 320 };

	// 縮小率
	wide = 1;
}