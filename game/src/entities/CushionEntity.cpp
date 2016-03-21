#include "CushionEntity.h"

CushionEntity::CushionEntity(CushionEntityParams params, RenderObject* ro, PhysicsObject* po, CollisionPlane* r)
	: Entity(EntityParams{ params.position, params.velocity, params.acceleration, params.rotation, params.mass, params.mesh, params.shader, params.name }, ro, po) {
	Entity::setCollisionShape(r);
}

CushionEntity::~CushionEntity() {}