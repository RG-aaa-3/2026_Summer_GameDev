#pragma once
#include "PeaceBase.h"

class PeaceT : public PeaceBase
{
public:
	PeaceT(
		int graphHandle,
		const std::vector<std::vector<int>>& shape,
		int startX,
		int startY,
		int cellSize
	);

	void SetPeacePram(void) override;
};