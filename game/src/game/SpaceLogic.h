#pragma once

#include "../../../engine-common/src/game/GameLogic.h"
#include "../states/PlayerState.h"

class SpaceLogic : public GameLogic
{
public:
	SpaceLogic();
	virtual ~SpaceLogic();
	bool init();
	bool destroy();
	void update(float msec);
private:
	PlayerState m_PlayerState;
};