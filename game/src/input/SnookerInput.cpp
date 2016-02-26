#include "SnookerInput.h"

using namespace engine::graphics;

SnookerInput::SnookerInput() {}

SnookerInput::~SnookerInput() {}

void SnookerInput::handleInput(float msec) {
	Window* window = Window::WindowPointer;
	if (window->isKeyPressed(GLFW_KEY_SPACE)) { m_CueBall->applyForce(vec3(0.0f, 0.001f, 0.0f)); }

}