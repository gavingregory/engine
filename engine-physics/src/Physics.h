#pragma once

#include <glm/glm.hpp>

namespace engine {
	namespace physics {
		using namespace glm;

		class Physics
		{
		public:
			Physics();
			virtual ~Physics();
			static vec3 updateVelocity(vec3 initialVelocity, vec3 acceleration, float time);
			static vec3 updateDisplacement(vec3 initialVelocity, vec3 acceleration, float time);
			static void explicitEuler(vec3& position, vec3& velocity, const vec3 acceleration, const float dt);
			static void implicitEuler(vec3& position, vec3& velocity, const vec3 acceleration, const float dt);
			static void semiImplicitEuler(vec3& position, vec3& velocity, const vec3 acceleration, const float dt);
			
			static void resolveCollision(vec3* velocity1, float firstMass, vec3* velocity2, float secondMass);
		};

	}
}

