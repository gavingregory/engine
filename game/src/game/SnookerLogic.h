#pragma once

#include "../../../engine-common/src/game/GameLogic.h"

class SnookerLogic : public GameLogic
{
public:
	SnookerLogic();
	virtual ~SnookerLogic();
	bool init() { return 1; }
	bool destroy() { return 1; }
	void update(float msec) { return; }
};

