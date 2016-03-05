#pragma once

#include "../system/SubSystem.h"

class GameLogic : public SubSystem
{
public:
	GameLogic();
	virtual ~GameLogic();
	virtual bool init() = 0;
	virtual bool destroy() = 0;
	virtual void update(float msec) = 0;
};

