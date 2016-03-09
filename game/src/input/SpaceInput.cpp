#include "SpaceInput.h"

SpaceInput::SpaceInput(Audio* audio, SpaceLogic* logic) {
	this->m_Audio = audio;
	this->m_GameLogic = logic;
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
		m_GameLogic->m_GameState = GS_BUILD;
		m_GameLogic->m_BuildState = BASIC_NODE;
	}
	else if (state == GLFW_RELEASE)
		m_KeysHeld[GLFW_KEY_1] = false;

	// BUILD
	state = glfwGetKey(m_GlfwWindow, GLFW_KEY_2);
	if (state == GLFW_PRESS && !m_KeysHeld[GLFW_KEY_2]) {
		m_KeysHeld[GLFW_KEY_2] = true;
		m_GameLogic->m_GameState = GS_BUILD;
		m_GameLogic->m_BuildState = HARVESTER_NODE;
	}
	else if (state == GLFW_RELEASE)
		m_KeysHeld[GLFW_KEY_2] = false;


	// BUILD
	state = glfwGetKey(m_GlfwWindow, GLFW_KEY_3);
	if (state == GLFW_PRESS && !m_KeysHeld[GLFW_KEY_3]) {
		m_KeysHeld[GLFW_KEY_3] = true;
		m_GameLogic->m_GameState = GS_BUILD;
		m_GameLogic->m_BuildState = ENERGY_NODE;
	}
	else if (state == GLFW_RELEASE)
		m_KeysHeld[GLFW_KEY_3] = false;

	// BUILD
	state = glfwGetKey(m_GlfwWindow, GLFW_KEY_4);
	if (state == GLFW_PRESS && !m_KeysHeld[GLFW_KEY_4]) {
		m_KeysHeld[GLFW_KEY_4] = true;
		m_GameLogic->m_GameState = GS_BUILD;
		m_GameLogic->m_BuildState = STORAGE_NODE;
	}
	else if (state == GLFW_RELEASE)
		m_KeysHeld[GLFW_KEY_4] = false;

	// BUILD
	state = glfwGetKey(m_GlfwWindow, GLFW_KEY_5);
	if (state == GLFW_PRESS && !m_KeysHeld[GLFW_KEY_5]) {
		m_KeysHeld[GLFW_KEY_5] = true;
		m_GameLogic->m_GameState = GS_BUILD;
		m_GameLogic->m_BuildState = LASER_NODE;
	}
	else if (state == GLFW_RELEASE)
		m_KeysHeld[GLFW_KEY_5] = false;

	// BUILD
	state = glfwGetKey(m_GlfwWindow, GLFW_KEY_ESCAPE);
	if (state == GLFW_PRESS && !m_KeysHeld[GLFW_KEY_ESCAPE]) {
		m_KeysHeld[GLFW_KEY_ESCAPE] = true;
		m_GameLogic->m_GameState = GS_SELECT;
	}
	else if (state == GLFW_RELEASE)
		m_KeysHeld[GLFW_KEY_ESCAPE] = false;

	// PLACE THE BUILDING
	state = glfwGetMouseButton(m_GlfwWindow, GLFW_MOUSE_BUTTON_1);
	if (state == GLFW_PRESS && !m_MouseButtonsHeld[GLFW_MOUSE_BUTTON_1] && m_GameLogic->m_GameState == GS_BUILD) {
		m_MouseButtonsHeld[GLFW_MOUSE_BUTTON_1] = true;
		m_GameLogic->m_GameState = GS_PLACING;
	}
	else if (state == GLFW_RELEASE)
		m_MouseButtonsHeld[GLFW_MOUSE_BUTTON_1] = false;

	// get mouse position
	vec2 mouse = Camera::calculateWorldPositionFromMouseCoords(vec2(m_Window->getMouseX(), m_Window->getMouseY()));
	m_GameLogic->m_MousePosition = mouse;

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
