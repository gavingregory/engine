#pragma once

#include "../../../engine-common/src/game/GameLogic.h"
#include "../memory/SpaceMemoryManager.h"
#include "../states/PlayerState.h"
#include <iostream>

using std::cout;
using std::endl;

enum GameState {
	GS_BUILD,
	GS_SELECT,
	GS_PLACING,
	GS_PAUSED
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
	SpaceLogic(SpaceMemoryManager* memory);
	virtual ~SpaceLogic();
	bool init();
	bool destroy();
	void update(float msec);
private:
	void buildBasicNode();
	GameState m_GameState;
	BuildState m_BuildState;
	Entity* m_BuildEntity;
	SpaceMemoryManager* m_MemoryManager;
	vec2 m_MousePosition;
};