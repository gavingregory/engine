#pragma once

#include "../graphics/Window.h"
#include "../system/SubSystem.h"
#include <glm/glm.hpp>

class InputHandler : public SubSystem
{
public:
	virtual void handleInput(float msec) =0;
	glm::vec2 getMouseRelative() {
		Window* window = Window::WindowPointer;
		return window->getMouseOffset();
	}
};