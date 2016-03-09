#pragma once

#include "../../../engine-common/src/game/GameLogic.h"
#include "../states/PlayerState.h"
#include <iostream>

using std::cout;
using std::endl;

enum GameState {
	BUILD_MODE,
	SELECT_MODE
};

enum BuildState {
	BASIC_NODE,
	HARVESTER_NODE,
	ENERGY_NODE,
	STORAGE_NODE,
	LASER_NODE
};

class SpaceLogic : public GameLogic
{
	friend class SpaceInput;
public:
	SpaceLogic();
	virtual ~SpaceLogic();
	bool init();
	bool destroy();
	void update(float msec);
private:
	GameState m_GameState;
	BuildState m_BuildState;
};