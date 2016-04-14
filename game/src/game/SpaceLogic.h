#pragma once

#include "../../../engine-common/src/game/GameLogic.h"
#include "../memory/SpaceMemoryManager.h"
#include "../input/SpaceInput.h"
#include "../states/PlayerState.h"
#include "GameStates.h"
#include <iostream>

using std::cout;
using std::endl;
using std::to_string;

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
	SpaceLogic(SpaceMemoryManager* memory, Physics* physics, InputHandler* inputHandler);
	virtual ~SpaceLogic();
	bool init();
	bool destroy();
	void update(float msec);
	void InputCallback(bool key, bool mouse, int id);
private:
	static int UniqueId;
	void buildBasicNode();
	GameState m_GameState;
	BuildState m_BuildState;
	Entity* m_BuildEntity;
	SpaceMemoryManager* m_MemoryManager;
	vec2 m_MousePosition;
};