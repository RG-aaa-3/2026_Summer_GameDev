#pragma once
#include "PeaceBase.h"

class PeaceZ : public PeaceBase
{
public:
	PeaceZ(
		int graphHandle,
		const std::vector<std::vector<int>>& shape,
		int startX,
		int startY,
		int cellSize
	);

	void SetPeacePram(void) override;
};