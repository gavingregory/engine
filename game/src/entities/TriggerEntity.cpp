#include "TriggerEntity.h"

TriggerEntity::TriggerEntity(TriggerEntityParams params, RenderObject* ro)
	: Entity(EntityParams{params.position, params.velocity, params.acceleration, params.rotation, params.mass, params.mesh, params.shader, params.name, params.category, params.hasPhysics, params.isSensor, params.bodyDef, params.shape}, ro) {

	// set box2d stuff
	m_PhysicsObject->SetAngularDamping(0.0000f);
	m_PhysicsObject->SetGravityScale(0.0f);
	m_Rotates = params.rotates;
	if (m_Rotates) {
		m_PhysicsObject->SetAngularVelocity(0.001f);
		m_PhysicsObject->SetAngularDamping(0.f);
	}
	m_CollisionCategory = COLLISION_TRIGGER;
	m_MaskBits = COLLISION_PLAYER;
}

TriggerEntity::~TriggerEntity() {}

void TriggerEntity::update(float msec) {
	Entity::update(msec);
}