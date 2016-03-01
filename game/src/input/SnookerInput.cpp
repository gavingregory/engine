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
		m_CueBall->applyForce(vec3(0.1f, 0.0f, 0.0f));
	}
	else if (state == GLFW_RELEASE)
		m_KeysHeld[GLFW_KEY_ENTER] = false;

	// handle the 'o' key
	state = glfwGetKey(glfwWindow, GLFW_KEY_O);
	if (state == GLFW_PRESS && !m_KeysHeld[GLFW_KEY_O]) {
		m_KeysHeld[GLFW_KEY_O] = true;
		m_Audio->play();
	}
	else if (state == GLFW_RELEASE)
		m_KeysHeld[GLFW_KEY_O] = false;

	// handle the 'p' key
	state = glfwGetKey(glfwWindow, GLFW_KEY_P);
	if (state == GLFW_PRESS && !m_KeysHeld[GLFW_KEY_P]) {
		m_KeysHeld[GLFW_KEY_P] = true;
		m_Audio->stop();
	}
	else if (state == GLFW_RELEASE)
		m_KeysHeld[GLFW_KEY_P] = false;

	// Camera controls
	state = glfwGetKey(glfwWindow, GLFW_KEY_E);
	if (state == GLFW_PRESS && !m_KeysHeld[GLFW_KEY_E]) {
		Camera::vw_matrix *= glm::translate(vec3(0, 0, 1));
	}
	state = glfwGetKey(glfwWindow, GLFW_KEY_Q);
	if (state == GLFW_PRESS && !m_KeysHeld[GLFW_KEY_Q]) {
		Camera::vw_matrix *= glm::translate(vec3(0, 0, -1));
	}

	// move a light source
#define WIDTH 800
#define HEIGHT 600
	Camera::light_src = glm::vec3(
		window->getMouseX() - WIDTH / 2,
		(HEIGHT-window->getMouseY()) - HEIGHT / 2,
		-300.0f);
	


}