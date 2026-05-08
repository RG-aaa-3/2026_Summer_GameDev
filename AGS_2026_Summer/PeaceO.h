#pragma once
#include "PeaceBase.h"

class PeaceO : public PeaceBase
{
public:
	PeaceO(
		int graphHandle,
		const std::vector<std::vector<int>>& shape,
		int startX,
		int startY,
		int cellSize
	);

	void SetPeacePram(void) override;
};