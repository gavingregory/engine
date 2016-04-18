#pragma once

#include "../../../engine-common/src/game/BaseLogic.h"
#include "../memory/GameMemoryManager.h"
#include "../input/GameInput.h"
#include "../states/PlayerState.h"
#include "GameStates.h"
#include <iostream>

using std::cout;
using std::endl;
using std::to_string;

class GameLogic : public BaseLogic
{
	friend class GameInput;
public:
	GameLogic(GameMemoryManager* memory, Physics* physics, InputHandler* inputHandler, Audio* audio);
	virtual ~GameLogic();
	bool init();
	bool destroy();
	void update(float msec);
	static BaseLogic* GameLogicInstance;
	static InputTypes PlayerMovementState;
private:
	static int UniqueId;
	Audio* m_Audio;
	GameMemoryManager* m_MemoryManager;
	vec2 m_MousePosition;
};