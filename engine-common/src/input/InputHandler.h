#pragma once

#include "../system/CallbackFunctions.h"
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
	void registerInputEventCallback(InputEventCallback cb) { m_InputEventCallback = cb; }
protected:
	InputEventCallback m_InputEventCallback; // call this function when an input event occurs!
};