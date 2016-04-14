#pragma once

#include "../../engine-common/src/system/CallbackFunctions.h"
#include "../../engine-common/src/system/SubSystem.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <iostream>
#include "collision\CollisionCircle.h"
#include "collision\CollisionShape.h"
#include "collision\CollisionPlane.h"

#define DAMPING_FACTOR 0.99f

using glm::vec3;

class Physics : public SubSystem
{
public:
	Physics();
	virtual ~Physics();
	bool init();
	bool destroy();
	void update(float msec);
	void registerCollisionEventCallback(CollisionEventCallback cb) { this->m_CollisionEventCallback = cb; }
private:
	CollisionEventCallback m_CollisionEventCallback; // call this function when a collision occurs!
};
