#include "BallEntity.h"

BallEntity::BallEntity(BallEntityParams params, RenderObject* ro, PhysicsObject* po)
	: Entity(EntityParams{params.position, params.velocity, params.acceleration, params.mesh, params.shader, params.name}, ro, po) {
	Entity::getPhysicsObject()->setCollisionShape(new Circle(Entity::getPhysicsObject()->getPositionPtr(), params.radius));
}

BallEntity::~BallEntity() {}