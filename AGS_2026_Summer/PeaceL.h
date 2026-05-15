#pragma once
#include "PeaceBase.h"

class PeaceL : public PeaceBase
{
public:
	PeaceL(
		int graphHandle,
		const std::vector<std::vector<int>>& shape,
		int startX,
		int startY,
		int cellSize
	);

	void SetPeacePram(void) override;
};