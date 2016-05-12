#include "EnemyEntity.h"

EnemyEntity::EnemyEntity(EnemyEntityParams params, RenderObject* ro)
	: Entity(EntityParams{params.position, params.velocity, params.acceleration, params.rotation, params.mass, params.mesh, params.shader, params.name, params.category, params.hasPhysics, params.isSensor, params.bodyDef, params.shape}, ro) {

	// set box2d stuff
	m_PhysicsObject->SetAngularDamping(0.0001f);
	m_PhysicsObject->SetLinearDamping(0.0001f);
	m_PhysicsObject->SetGravityScale(0.0f);
	m_Waypoints[0] = params.waypoints0;
	m_Waypoints[1] = params.waypoints1;
	m_Waypoints[2] = params.waypoints2;
	m_Waypoints[3] = params.waypoints3;
	m_LoopWaypoints = params.loopWaypoints;
	m_NumWaypoints = params.numWaypoints;
	m_Rotates = params.rotates;

	if (m_Rotates) {
		m_PhysicsObject->SetAngularVelocity(0.001f);
		m_PhysicsObject->SetAngularDamping(0.f);
	}
	m_CollisionCategory = COLLISION_ENEMY;
	m_MaskBits = COLLISION_PLAYER;
}

EnemyEntity::~EnemyEntity() {}

void EnemyEntity::update(float msec) {
	Entity::update(msec);

	float distance = b2Distance(m_PhysicsObject->GetPosition(), m_Waypoints[m_CurrentWaypoint]);
	if (distance < 1.0f && m_NumWaypoints) {
		if (m_LoopWaypoints) {
			m_CurrentWaypoint = ((m_CurrentWaypoint + 1) % m_NumWaypoints) % MAX_WAYPOINTS;
		}
		else {
			m_CurrentWaypoint--;
			if (m_CurrentWaypoint < 0) m_CurrentWaypoint = m_NumWaypoints-1;
		}
	}
	// apply velocity towards next object
	if (m_NumWaypoints) {
		b2Vec2 velocity = m_Waypoints[m_CurrentWaypoint] - m_PhysicsObject->GetPosition();
		velocity.Normalize();
		velocity *= 0.09f;
		m_PhysicsObject->SetLinearVelocity(velocity);
	}
}