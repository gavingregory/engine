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

class SpaceInput : public InputHandler
{
public:
	SpaceInput(Audio* audio);
	virtual ~SpaceInput();
	void handleInput(float msec) override;
	virtual bool init();
	virtual bool destroy();
	virtual void update(float msec);
private:
	bool        m_KeysHeld[MAX_KEYS];
	bool        m_MouseButtonsHeld[MAX_BUTTONS];
	Audio*      m_Audio;
	Window*     m_Window;
	GLFWwindow* m_GlfwWindow;
};