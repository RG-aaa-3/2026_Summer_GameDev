#include "PeaceL.h"
#include <DxLib.h>

PeaceL::PeaceL(
	int graphHandle,
	const std::vector<std::vector<int>>& shape,
	int startX,
	int startY,
	int cellSize
)
	: PeaceBase(graphHandle, shape, startX, startY, cellSize)
{
}

void PeaceL::SetPeacePram(void) {
	// 画像ファイル名
	imgFName = "PeaceL.png";

	// 元画像サイズ
	size = { 320, 320 };

	// 縮小率
	wide = 1;
}