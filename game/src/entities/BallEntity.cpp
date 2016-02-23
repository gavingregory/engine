#include "BallEntity.h"

BallEntity::BallEntity()
	: Entity(glm::vec3(0), glm::vec3(0), glm::vec3(0), RenderObject(), "ball") {

}

BallEntity::BallEntity(glm::vec3 position, glm::vec3 velocity, glm::vec3 acceleration, RenderObject o, string name, glm::vec4 colour)
	: Entity(position, velocity, acceleration, o, name) {
	renderObject.pushUniformVec4("col", colour);
}

BallEntity::~BallEntity() {}

void BallEntity::update(float msec) {
	if (engine::graphics::Window::WindowPointer->isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT)) {
		*acceleration = glm::vec3(-0.001f, 0.0f, 0.0f);
		*velocity = glm::vec3(0.1f, 0.0f, 0.0f);
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