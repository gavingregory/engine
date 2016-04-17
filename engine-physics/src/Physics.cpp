#include "Physics.h"

b2World* Physics::CurrentWorld;

Physics::Physics(float gravity) : m_Gravity(gravity), m_World(b2Vec2(0.0f, gravity)) {
	m_World.SetAllowSleeping(false);
	Physics::CurrentWorld = &m_World;
}

Physics::~Physics() {}

bool Physics::init() {
	return 1;
}

bool Physics::destroy() {
	return 1;
}

void Physics::update(float msec) {
	
}