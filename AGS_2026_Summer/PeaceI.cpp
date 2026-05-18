#include "PeaceI.h"
#include <DxLib.h>

PeaceI::PeaceI(
	int graphHandle,
	const std::vector<std::vector<int>>& shape,
	int startX,
	int startY,
	int cellSize
)
	: PeaceBase(graphHandle, shape, startX, startY, cellSize)
{
}

void PeaceI::SetPeacePram(void) {
	// 画像ファイル名
	imgFName = "PeaceI.png";

	// 元画像サイズ
	size = { 320, 320 };

	// 縮小率
	wide = 1;
}