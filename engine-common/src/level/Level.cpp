#include "Level.h"

Level::Level(LevelParams params) {
	m_Renderer = params.renderer;
}

Level::~Level() { }

bool Level::init() { return 0; }

bool Level::destroy() { return 0; }

void Level::update(float msec) {

	// UPDATE
	for (map<string, Entity*>::iterator it = m_Entities.begin(); it != m_Entities.end(); ++it) {
		(it->second)->update(msec);
	}

	// COLLISION
	for (unsigned int i = 0; i < PhysicsObject::m_Colliders.size(); i++) {
		for (unsigned int j = 0; j < PhysicsObject::m_Colliders.size(); j++) {
			if (i != j) {
				if (!PhysicsObject::m_Colliders[i]->isColliding(PhysicsObject::m_Colliders[j])) {
					if (Physics::detectCollision(
						PhysicsObject::m_Colliders[i]->m_Velocity, PhysicsObject::m_Colliders[i]->m_Mass, (CollisionCircle*)PhysicsObject::m_Colliders[i]->getCollisionShape(), PhysicsObject::m_Colliders[i]->m_Position,
						PhysicsObject::m_Colliders[j]->m_Velocity, PhysicsObject::m_Colliders[j]->m_Mass, (CollisionCircle*)PhysicsObject::m_Colliders[j]->getCollisionShape(), PhysicsObject::m_Colliders[j]->m_Position,
						1.0f)) {
						PhysicsObject::m_Colliders[i]->collide(PhysicsObject::m_Colliders[j]);
						PhysicsObject::m_Colliders[j]->collide(PhysicsObject::m_Colliders[i]);
					}
				}
				else {
					PhysicsObject::m_Colliders[i]->noCollide(PhysicsObject::m_Colliders[j]);
					PhysicsObject::m_Colliders[j]->noCollide(PhysicsObject::m_Colliders[i]);
				}

			}
		}
	}

	// RENDER
	for (map<string, Entity*>::iterator it = m_Entities.begin(); it != m_Entities.end(); ++it) {
		(it->second)->render(m_Renderer);
	}

	// GAME LOGIC
	//m_GameLogic->update(msec);
}