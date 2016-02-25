#include "SnookerInput.h"

using namespace engine::graphics;

SnookerInput::SnookerInput() {}

SnookerInput::~SnookerInput() {}

void SnookerInput::handleInput(float msec) {
	Window* window = Window::WindowPointer;
	if (window->isKeyPressed(GLFW_KEY_W)) { Camera::vw_matrix *= glm::rotate(0.01f, glm::vec3(1, 0, 0)); }
	if (window->isKeyPressed(GLFW_KEY_S)) { Camera::vw_matrix *= glm::rotate(0.01f, glm::vec3(-1, 0, 0)); }
	if (window->isKeyPressed(GLFW_KEY_A)) { Camera::vw_matrix *= glm::rotate(0.01f, glm::vec3(0, 1, 0)); }
	if (window->isKeyPressed(GLFW_KEY_D)) { Camera::vw_matrix *= glm::rotate(0.01f, glm::vec3(0, -1, 0)); }

	if (window->isKeyPressed(GLFW_KEY_SPACE)) { m_CueBall->applyForce(vec3(0.0f, 0.0f, 0.001f)); }

}