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
	if (state == GLFW_PRESS && !m_MouseButtonsHeld[GLFW_MOUSE_BUTTON_LEFT]) {
		m_MouseButtonsHeld[GLFW_MOUSE_BUTTON_LEFT] = true;
		vec3 cueBallPosition = m_CueBall->getPosition();
		vec3 clickPosition(Camera::calculateWorldPositionFromMouseCoords(vec2(window->getMouseX(), window->getMouseY())), cueBallPosition.z);
		vec3 direction = clickPosition - cueBallPosition;
		vec3 force = glm::normalize(direction) * (glm::length(direction) / 500.0f);
		m_CueBall->applyForce(force);
	}
	else if (state == GLFW_RELEASE) {
		m_MouseButtonsHeld[GLFW_MOUSE_BUTTON_LEFT] = false;
	}

	// Camera controls
	state = glfwGetKey(glfwWindow, GLFW_KEY_E);
	if (state == GLFW_PRESS && !m_KeysHeld[GLFW_KEY_E]) {
		Camera::width -= 0.99f;
		Camera::pr_matrix = glm::ortho(-(Camera::width / 2), (Camera::width / 2), -(Camera::width / 2), (Camera::width / 2), 0.0f, 100.0f);
	}
	state = glfwGetKey(glfwWindow, GLFW_KEY_Q);
	if (state == GLFW_PRESS && !m_KeysHeld[GLFW_KEY_Q]) {
		Camera::width += 0.99f;
		Camera::pr_matrix = glm::ortho(-(Camera::width / 2), (Camera::width / 2), -(Camera::width / 2), (Camera::width / 2), 0.0f, 100.0f);
	}

	// get mouse position
	vec2 mouse = Camera::calculateWorldPositionFromMouseCoords(vec2(window->getMouseX(), window->getMouseY()));

	// rotate cue depending on mouse coords
	vec3 mouseFromCueVector = vec3(mouse, 0) - m_CueBall->getPosition();
	float angle = glm::angle(glm::normalize(mouseFromCueVector), glm::normalize(vec3(0, 1, 0)));
	//cout << glm::degrees(angle) << endl;
	if (mouseFromCueVector.x >= 0) angle = -angle;
	m_Cue->setRotation(angle);

	// set light source to follow mouse
	vec3 cueBallPos = m_CueBall->getPosition(); //vec3(mouse, 300);
	cueBallPos.z = 100;
	Camera::light_src = vec3(mouse, 0.0f);
}

bool SnookerInput::init() {
	// init
	return true;
}

bool SnookerInput::destroy() {
	// destroy
	return 0;
}

void SnookerInput::update(float msec) {
	// do nothing
}
