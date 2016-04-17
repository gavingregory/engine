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

class SpaceLogic : public GameLogic
{
	friend class SpaceInput;
public:
	SpaceLogic(SpaceMemoryManager* memory, Physics* physics, InputHandler* inputHandler);
	virtual ~SpaceLogic();
	bool init();
	bool destroy();
	void update(float msec);
	static SpaceLogic* GameLogicInstance;
	static InputTypes PlayerMovementState;
private:
	static int UniqueId;
	SpaceMemoryManager* m_MemoryManager;
	vec2 m_MousePosition;
};