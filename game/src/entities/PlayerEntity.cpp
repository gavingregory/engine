#include "PlayerEntity.h"

PlayerEntity::PlayerEntity(PlayerEntityParams params, RenderObject* ro)
	: Entity(EntityParams{params.position, params.velocity, params.acceleration, params.rotation, params.mass, params.mesh, params.shader, params.name, params.bodyDef, params.shape}, ro) {

	// set box2d stuff
	m_PhysicsObject->SetAngularDamping(0.001f);
}

PlayerEntity::~PlayerEntity() {}

void PlayerEntity::boost() {
	float magnitude = 2.2f;
	b2Vec2 force = b2Vec2(cos(m_PhysicsObject->GetAngle()) * magnitude, sin(m_PhysicsObject->GetAngle()) * magnitude);
	m_PhysicsObject->ApplyForce(force, m_PhysicsObject->GetPosition(), true);
	cout << "boost!" << endl;
}

void PlayerEntity::rotate(float angle) {
	m_PhysicsObject->SetAngularVelocity(angle);
}