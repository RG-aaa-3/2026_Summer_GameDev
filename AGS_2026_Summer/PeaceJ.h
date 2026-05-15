#pragma once
#include "PeaceBase.h"

class PeaceJ : public PeaceBase
{
public:
	PeaceJ(
		int graphHandle,
		const std::vector<std::vector<int>>& shape,
		int startX,
		int startY,
		int cellSize
	);

	void SetPeacePram(void) override;
};