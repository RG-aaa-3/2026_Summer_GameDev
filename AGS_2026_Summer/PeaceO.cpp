#include "PeaceO.h"
#include <DxLib.h>

PeaceO::PeaceO(
	int graphHandle,
	const std::vector<std::vector<int>>& shape,
	int startX,
	int startY,
	int cellSize
)
	: PeaceBase(graphHandle, shape, startX, startY, cellSize)
{
}

void PeaceO::SetPeacePram(void) {
	// 画像ファイル名
	imgFName = "PeaceO.png";

	// 元画像サイズ
	size = { 500, 500 };

	// 縮小率
	wide = 10;
}