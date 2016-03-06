#pragma once

#include "../../../engine-common/src/game/GameLogic.h"

class SpaceLogic : public GameLogic
{
public:
	SpaceLogic();
	virtual ~SpaceLogic();
	bool init() { return 1; }
	bool destroy() { return 1; }
	void update(float msec) { return; }
};

