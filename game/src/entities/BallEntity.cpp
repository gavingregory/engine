#include "BallEntity.h"

BallEntity::BallEntity(BallEntityParams params, RenderObject* ro, PhysicsObject* po, CollisionCircle* c)
	: Entity(EntityParams{params.position, params.velocity, params.acceleration, params.rotation, params.mass, params.mesh, params.shader, params.name}, ro, po) {
	Entity::getPhysicsObject()->setCollisionShape(c);
}

BallEntity::~BallEntity() {}