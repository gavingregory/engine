#include "BallEntity.h"

BallEntity::BallEntity(glm::vec3 position, glm::vec3 velocity, glm::vec3 acceleration, Mesh* mesh, Shader* shader, float radius, string name)
	: Entity(position, velocity, acceleration, mesh, shader, name) {
	Entity::getPhysicsObject()->setCollisionShape(new Circle(Entity::getPhysicsObject()->getPositionPtr(), radius));
}

BallEntity::~BallEntity() {}
