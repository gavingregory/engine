#pragma once

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <iostream>
#include "collision\CollisionCircle.h"
#include "collision\CollisionShape.h"
#include "collision\CollisionPlane.h"

#define DAMPING_FACTOR 0.8f

using glm::vec3;

class Physics
{
public:
	Physics();
	virtual ~Physics();
	static vec3 updateVelocity(vec3 initialVelocity, vec3 acceleration, float time);
	static vec3 updateDisplacement(vec3 initialVelocity, vec3 acceleration, float time);
	static void explicitEuler(vec3& position, vec3& velocity, const vec3 acceleration, const float dt);
	static void implicitEuler(vec3& position, vec3& velocity, const vec3 acceleration, const float dt);
	static void semiImplicitEuler(vec3& position, vec3& velocity, const vec3 acceleration, vec3& displacement, const float dt);

	static bool detectCollision(vec3& vec0, float m0, CollisionShape* c0, vec3& pos0, vec3& v1, float m1, CollisionShape* c1, vec3& pos1, float coeffElasticity);
	static bool handleCircleCircle(vec3& vel0, float m0, CollisionCircle* c0, vec3& pos0, vec3& vel1, float m1, CollisionCircle* c1, vec3& pos1, float coeffElasticity);
	static bool handleCirclePlane(vec3& vel0, float m0, CollisionCircle* c0, vec3& pos0, vec3& vel1, float m1, CollisionPlane* c1, vec3& pos1, float coeffElasticity);
};
