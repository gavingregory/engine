#include "Physics.h"

Physics::Physics(float gravity) : m_Gravity(gravity), m_World(b2Vec2(0.0f, gravity)) {}
Physics::~Physics() {}

bool Physics::init() {
	return 1;
}

bool Physics::destroy() {
	return 1;
}

void Physics::update(float msec) {
	
}