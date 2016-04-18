/******************************************************************************
Class:GameInput
Author:Gavin Gregory
Description:A subclass of the InputHandler class which handles all game input
related functionality.
*//////////////////////////////////////////////////////////////////////////////

#pragma once
#include "../../../engine-common/src/input/InputHandler.h"
#include "../../../engine-common/src/graphics/Window.h"
#include "../entities/PlayerEntity.h"
#include "../game/GameStates.h"
#include "../../../engine-audio/src/Audio.h"
#include "../../../engine-common/src/graphics/Camera.h"
#include "../../../engine-audio/src/Audio.h"
#include "../../../engine-common/src/level/Level.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#define MAX_KEYS 1024

class GameInput : public InputHandler
{
public:
	GameInput(Audio* audio);
	virtual ~GameInput();
	void handleInput(float msec) override;
	virtual bool init();
	virtual bool destroy();
	virtual void update(float msec);
	static bool KeysHeld[MAX_KEYS];
	static bool MouseButtonsHeld[MAX_BUTTONS];
private:
	Audio*      m_Audio;
	Window*     m_Window;
	GLFWwindow* m_GlfwWindow;
};