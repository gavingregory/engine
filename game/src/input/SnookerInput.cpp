#include "SnookerInput.h"

using namespace engine::graphics;

SnookerInput::SnookerInput() {
	for (int i = 0; i < MAX_KEYS; i++)
		m_KeysHeld[i] = false;
}

SnookerInput::~SnookerInput() {}

void SnookerInput::handleInput(float msec) {
	Window* window = Window::WindowPointer;
	GLFWwindow* glfwWindow = window->getGlfwWindow();
	//if (window->isKeyPressed(GLFW_KEY_SPACE)) { m_CueBall->applyForce(vec3(0.1f, 0.1f, 0.0f), vec3(-0.009, -0.009, 0)); }
	
	// handle the enter key
	int state = glfwGetKey(glfwWindow, GLFW_KEY_ENTER);
	if (state == GLFW_PRESS && !m_KeysHeld[GLFW_KEY_ENTER]) { 
		m_KeysHeld[GLFW_KEY_ENTER] = true;
		m_CueBall->applyForce(vec3(0.1f, 0.1f, 0.0f), vec3(-0.0001, -0.0001, 0.0f));
	}
	else if (state == GLFW_RELEASE)
		m_KeysHeld[GLFW_KEY_ENTER] = false;
}