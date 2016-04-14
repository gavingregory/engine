#pragma once

#include "../../engine-common/src/system/CallbackFunctions.h"
#include "../../engine-common/src/system/SubSystem.h"
#include <Box2D\Box2D.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <iostream>

using glm::vec3;

class Physics : public SubSystem
{
public:
	Physics(float gravity);
	virtual ~Physics();
	bool init();
	bool destroy();
	void update(float msec);
	void registerCollisionEventCallback(CollisionEventCallback cb) { this->m_CollisionEventCallback = cb; }
	static b2World* CurrentWorld;
private:
	CollisionEventCallback m_CollisionEventCallback; // call this function when a collision occurs!
	float m_Gravity;
	b2World m_World;
};
