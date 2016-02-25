#include "BallEntity.h"

BallEntity::BallEntity(glm::vec3 position, glm::vec3 velocity, glm::vec3 acceleration, Mesh* mesh, Shader* shader, string name)
	: Entity(position, velocity, acceleration, mesh, shader, name) { }

BallEntity::~BallEntity() {}

void BallEntity::update(float msec) {
	if (engine::graphics::Window::WindowPointer->isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT)) {
		*acceleration = glm::vec3(-0.01f, 0.0f, 0.0f);
		*velocity = glm::vec3(0.8f, 0.0f, 0.0f);
	}

	*velocity = engine::graphics::Physics::updateVelocity(*velocity, *acceleration, msec);

	*position += engine::graphics::Physics::updateDisplacement(*velocity, *acceleration, msec);

	// slow down
	if ((*velocity).x < 0.0001f && (*velocity).y < 0.0001f && (*velocity).z < 0.0001f) {
		*acceleration = glm::vec3(0);
		*velocity = glm::vec3(0);
	}

	renderObject.SetModelMatrix(glm::translate(*this->position));
	renderObject.Update(msec);
}