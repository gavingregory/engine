#include "PlayerEntity.h"

PlayerEntity::PlayerEntity(PlayerEntityParams params, RenderObject* ro)
	: Entity(EntityParams{params.position, params.velocity, params.acceleration, params.rotation, params.mass, params.mesh, params.shader, params.name, params.category, params.hasPhysics, params.bodyDef, params.shape}, ro) {

	// set box2d stuff
	m_PhysicsObject->SetAngularDamping(0.0001f);
	m_PhysicsObject->SetLinearDamping(0.0001f);
	m_EngineSound == nullptr;
}

PlayerEntity::~PlayerEntity() {}

void PlayerEntity::boost() {
	if (m_EngineSound == nullptr) {
		m_EngineSound = Audio::Instance->play("res/audio/engine.mp3", true);
		m_EngineSound->setVolume(0.1f);
	}
	float magnitude = 0.1f;
	m_EngineSound->setVolume(1.0f);
	b2Vec2 force = b2Vec2(cos(m_PhysicsObject->GetAngle()) * magnitude, sin(m_PhysicsObject->GetAngle()) * magnitude);
	m_PhysicsObject->ApplyForce(force, m_PhysicsObject->GetWorldCenter(), true);
}

void PlayerEntity::stop() {
	if (m_EngineSound) m_EngineSound->setVolume(0.4f);
}

void PlayerEntity::rotate(float angle) {
	m_PhysicsObject->SetAngularVelocity(angle);
}