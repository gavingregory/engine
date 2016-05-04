#include "EnemyEntity.h"

EnemyEntity::EnemyEntity(EnemyEntityParams params, RenderObject* ro)
	: Entity(EntityParams{params.position, params.velocity, params.acceleration, params.rotation, params.mass, params.mesh, params.shader, params.name, params.category, params.hasPhysics, params.bodyDef, params.shape}, ro) {

	// set box2d stuff
	m_PhysicsObject->SetAngularDamping(0.0001f);
	m_PhysicsObject->SetLinearDamping(0.0001f);
	m_PhysicsObject->SetGravityScale(0.0f);
}

EnemyEntity::~EnemyEntity() {}