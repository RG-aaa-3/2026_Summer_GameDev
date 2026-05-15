#pragma once
#include "PeaceBase.h"

class PeaceS : public PeaceBase
{
public:
	PeaceS(
		int graphHandle,
		const std::vector<std::vector<int>>& shape,
		int startX,
		int startY,
		int cellSize
	);

	void SetPeacePram(void) override;
};