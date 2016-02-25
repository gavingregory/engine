#pragma once

#include "../graphics/Window.h"
#include <glm/glm.hpp>

class InputHandler
{
public:
	virtual void handleInput(float msec) =0;
	glm::vec2 getMouseRelative() {
		engine::graphics::Window* window = engine::graphics::Window::WindowPointer;
		return window->getMouseOffset();
	}
};