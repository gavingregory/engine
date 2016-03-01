#pragma once

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <iostream>
#include "collision\CollisionCircle.h"

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

	static bool handleCollision(vec3& vec0, float m0, CollisionCircle* c0, vec3& pos0, vec3& v1, float m1, CollisionCircle* c1, vec3& pos1, float coeffElasticity);
	static bool detectCollision(CollisionCircle* left, CollisionCircle* right, float& distance);
	static void resolveCollision(vec3 P, vec3 N, float p, vec3& v0, float m0, vec3& v1, float m1, float coeffElasticity);
};
