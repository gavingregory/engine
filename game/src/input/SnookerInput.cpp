#include "SnookerInput.h"

SnookerInput::SnookerInput() {
	for (int i = 0; i < MAX_KEYS; i++)
		m_KeysHeld[i] = false;
	for (int i = 0; i < MAX_BUTTONS; i++)
		m_MouseButtonsHeld[i] = false;
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
		m_CueBall->applyForce(vec3(-0.1f, 0.0f, 0.0f));
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
	
	// handle the left click
	state = glfwGetMouseButton(glfwWindow, GLFW_MOUSE_BUTTON_LEFT);
	if (state == GLFW_PRESS && !m_KeysHeld[GLFW_MOUSE_BUTTON_LEFT]) {
		vec2 clickPosition = Camera::calculateWorldPositionFromMouseCoords(vec2(window->getMouseX(), window->getMouseY()));
		vec3 cueBallPosition = m_CueBall->getPosition();
		vec3 click3Position = vec3(clickPosition, cueBallPosition.z);
		vec3 direction = click3Position - cueBallPosition;
		direction /= 10000;
		m_CueBall->applyForce(direction);
	}
	else if (state == GLFW_RELEASE) {
		m_MouseButtonsHeld[GLFW_MOUSE_BUTTON_LEFT] = false;
	}

	// Camera controls
	state = glfwGetKey(glfwWindow, GLFW_KEY_E);
	if (state == GLFW_PRESS && !m_KeysHeld[GLFW_KEY_E]) {
		Camera::width -= 0.15f;
		Camera::pr_matrix = glm::ortho(-(Camera::width / 2), (Camera::width / 2), -(Camera::width / 2), (Camera::width / 2), 0.0f, 100.0f);
	}
	state = glfwGetKey(glfwWindow, GLFW_KEY_Q);
	if (state == GLFW_PRESS && !m_KeysHeld[GLFW_KEY_Q]) {
		Camera::width += 0.15f;
		Camera::pr_matrix = glm::ortho(-(Camera::width / 2), (Camera::width / 2), -(Camera::width / 2), (Camera::width / 2), 0.0f, 100.0f);
	}

	cout << window->getMouseX() << ", " << window->getMouseY() << ", " << endl;
	Camera::light_src = vec3(Camera::calculateWorldPositionFromMouseCoords(vec2(window->getMouseX(), window->getMouseY())), 300);
}

bool SnookerInput::init() {
	// init
	return 0;
}

bool SnookerInput::destroy() {
	// destroy
	return 0;
}

void SnookerInput::update(float msec) {
	// do nothing
}
