#include "GameInput.h"

bool GameInput::KeysHeld[MAX_KEYS];
bool GameInput::MouseButtonsHeld[MAX_BUTTONS];

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS) {
		GameInput::KeysHeld[key] = true;
	}
	else if (action == GLFW_RELEASE) {
		GameInput::KeysHeld[key] = false;
	}
}

GameInput::GameInput(Audio* audio) {
	this->m_Audio = audio;
	for (int i = 0; i < MAX_KEYS; i++)
		GameInput::KeysHeld[i] = false;
	for (int i = 0; i < MAX_BUTTONS; i++)
		GameInput::MouseButtonsHeld[i] = false;
}

GameInput::~GameInput() {}

void GameInput::handleInput(float msec) {

	map<string, Entity*>* entities = Level::LevelStack.top()->getEntities();
	PlayerEntity* player = (PlayerEntity*)entities->at("ship");
	if (GameInput::KeysHeld[GLFW_KEY_W]) { player->boost(); }
	if (GameInput::KeysHeld[GLFW_KEY_A]) { player->rotate(0.001f); }
	if (GameInput::KeysHeld[GLFW_KEY_D]) { player->rotate(-0.001f); }
}

bool GameInput::init() {
	m_Window = Window::WindowPointer;
	m_GlfwWindow = m_Window->getGlfwWindow();
	glfwSetKeyCallback(m_GlfwWindow, key_callback);
	if (!m_Window) return false;
	if (!m_GlfwWindow) return false;
	return true;
}

bool GameInput::destroy() {
	// destroy
	return 0;
}

void GameInput::update(float msec) {
	// do nothing
}
