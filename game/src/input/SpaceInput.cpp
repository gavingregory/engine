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
		m_InputEventCallback(true, true, GLFW_KEY_W);
	}
	else if (state == GLFW_RELEASE && m_KeysHeld[GLFW_KEY_W]) {
		m_InputEventCallback(true, false, GLFW_KEY_W);
		m_KeysHeld[GLFW_KEY_W] = false;
	}

	state = glfwGetKey(m_GlfwWindow, GLFW_KEY_S);
	if (state == GLFW_PRESS && !m_KeysHeld[GLFW_KEY_S]) {
		m_KeysHeld[GLFW_KEY_S] = true;
		m_InputEventCallback(true, true, GLFW_KEY_S);
	}
	else if (state == GLFW_RELEASE && m_KeysHeld[GLFW_KEY_S]) {
		m_InputEventCallback(true, false, GLFW_KEY_S);
		m_KeysHeld[GLFW_KEY_S] = false;
	}

	state = glfwGetKey(m_GlfwWindow, GLFW_KEY_A);
	if (state == GLFW_PRESS && !m_KeysHeld[GLFW_KEY_A]) {
		m_KeysHeld[GLFW_KEY_A] = true;
		m_InputEventCallback(true, true, GLFW_KEY_A);
	}
	else if (state == GLFW_RELEASE && m_KeysHeld[GLFW_KEY_A]) {
		m_InputEventCallback(true, false, GLFW_KEY_A);
		m_KeysHeld[GLFW_KEY_A] = false;
	}

	state = glfwGetKey(m_GlfwWindow, GLFW_KEY_D);
	if (state == GLFW_PRESS && !m_KeysHeld[GLFW_KEY_D]) {
		m_KeysHeld[GLFW_KEY_D] = true;
		m_InputEventCallback(true, true, GLFW_KEY_D);
	}
	else if (state == GLFW_RELEASE && m_KeysHeld[GLFW_KEY_D]) {
		m_InputEventCallback(true, false, GLFW_KEY_D);
		m_KeysHeld[GLFW_KEY_D] = false;
	}
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
