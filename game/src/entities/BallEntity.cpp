#include "BallEntity.h"

BallEntity::BallEntity(BallEntityParams params)
	: Entity(EntityParams{params.position, params.velocity, params.acceleration, params.mesh, params.shader, params.name}) {
	Entity::getPhysicsObject()->setCollisionShape(new Circle(Entity::getPhysicsObject()->getPositionPtr(), params.radius));
}

BallEntity::~BallEntity() {}