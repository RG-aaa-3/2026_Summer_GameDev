#pragma once
#include "PeaceBase.h"

class PeaceI : public PeaceBase
{
public:
	PeaceI(
		int graphHandle,
		const std::vector<std::vector<int>>& shape,
		int startX,
		int startY,
		int cellSize
	);

	void SetPeacePram(void) override;
};