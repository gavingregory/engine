#include "SpaceInput.h"

bool SpaceInput::KeysHeld[MAX_KEYS];
bool SpaceInput::MouseButtonsHeld[MAX_BUTTONS];

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS) {
		SpaceInput::KeysHeld[key] = true;
	}
	else if (action == GLFW_RELEASE) {
		SpaceInput::KeysHeld[key] = false;
	}
}

SpaceInput::SpaceInput(Audio* audio) {
	this->m_Audio = audio;
	for (int i = 0; i < MAX_KEYS; i++)
		SpaceInput::KeysHeld[i] = false;
	for (int i = 0; i < MAX_BUTTONS; i++)
		SpaceInput::MouseButtonsHeld[i] = false;
}

SpaceInput::~SpaceInput() {}

void SpaceInput::handleInput(float msec) {

	map<string, Entity*>* entities = Level::currentLevel->getEntities();
	PlayerEntity* player = (PlayerEntity*)entities->at("ship");

	if (SpaceInput::KeysHeld[GLFW_KEY_W]) { player->boost(); cout << "boost" << endl; }
	if (SpaceInput::KeysHeld[GLFW_KEY_A]) { player->rotate(0.001f); cout << "boost" << endl; }
	if (SpaceInput::KeysHeld[GLFW_KEY_D]) { player->rotate(-0.001f); cout << "boost" << endl; }
}

bool SpaceInput::init() {
	m_Window = Window::WindowPointer;
	m_GlfwWindow = m_Window->getGlfwWindow();
	glfwSetKeyCallback(m_GlfwWindow, key_callback);
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
