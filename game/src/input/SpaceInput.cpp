#include "SpaceInput.h"

SpaceInput::SpaceInput() {
	for (int i = 0; i < MAX_KEYS; i++)
		m_KeysHeld[i] = false;
	for (int i = 0; i < MAX_BUTTONS; i++)
		m_MouseButtonsHeld[i] = false;
}

SpaceInput::~SpaceInput() {}

void SpaceInput::handleInput(float msec) {
	// BUILD
	int state = glfwGetKey(m_GlfwWindow, GLFW_KEY_1);
	if (state == GLFW_PRESS && !m_KeysHeld[GLFW_KEY_1]) {
		m_KeysHeld[GLFW_KEY_1] = true;
		// do something
	}
	else if (state == GLFW_RELEASE)
		m_KeysHeld[GLFW_KEY_1] = false;

	// get mouse position
	vec2 mouse = Camera::calculateWorldPositionFromMouseCoords(vec2(m_Window->getMouseX(), m_Window->getMouseY()));

	// set light source to follow mouse
	vec3 cueBallPos = vec3(mouse, 100);
	Camera::light_src = cueBallPos;
}

bool SpaceInput::init() {
	m_Window = Window::WindowPointer;
	m_GlfwWindow = m_Window->getGlfwWindow();
	if (!m_Window) return false;
	if (!m_GlfwWindow) return false;
	return true;
}

bool SpaceInput::destroy() {
	// destroy
	return 0;
}

void SpaceInput::update(float msec) {
	// do nothing
}
