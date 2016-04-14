#include "SpaceInput.h"

SpaceInput::SpaceInput(Audio* audio) {
	this->m_Audio = audio;
	for (int i = 0; i < MAX_KEYS; i++)
		m_KeysHeld[i] = false;
	for (int i = 0; i < MAX_BUTTONS; i++)
		m_MouseButtonsHeld[i] = false;
}

SpaceInput::~SpaceInput() {}

void SpaceInput::handleInput(float msec) {
	// Player Up Event
	int state = glfwGetKey(m_GlfwWindow, GLFW_KEY_W);
	if (state == GLFW_PRESS && !m_KeysHeld[GLFW_KEY_W]) {
		m_KeysHeld[GLFW_KEY_W] = true;
		m_InputEventCallback(true, false, IT_PLAYER_UP);
	}
	else if (state == GLFW_RELEASE)
		m_KeysHeld[GLFW_KEY_W] = false;
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
