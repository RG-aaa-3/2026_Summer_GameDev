#include "PeaceJ.h"
#include <DxLib.h>

PeaceJ::PeaceJ(
	int graphHandle,
	const std::vector<std::vector<int>>& shape,
	int startX,
	int startY,
	int cellSize
)
	: PeaceBase(graphHandle, shape, startX, startY, cellSize)
{
}

void PeaceJ::SetPeacePram(void) {
	// 画像ファイル名
	imgFName = "PeaceJ.png";

	// 元画像サイズ
	size = { 240, 320 };

	// 縮小率
	wide = 1;
}