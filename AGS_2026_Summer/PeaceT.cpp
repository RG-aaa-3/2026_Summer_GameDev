#include "PeaceT.h"
#include <DxLib.h>

PeaceT::PeaceT(
	int graphHandle,
	const std::vector<std::vector<int>>& shape,
	int startX,
	int startY,
	int cellSize
)
	: PeaceBase(graphHandle, shape, startX, startY, cellSize)
{
}

void PeaceT::SetPeacePram(void) {
	// 画像ファイル名
	imgFName = "PeaceT.png";

	// 元画像サイズ
	size = { 240, 320 };

	// 縮小率
	wide = 1;
}