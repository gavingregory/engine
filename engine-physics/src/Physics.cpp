#include "Physics.h"

namespace engine {
	namespace physics {

		Physics::Physics() {}
		Physics::~Physics() {}

		vec3 Physics::updateVelocity(vec3 initialVelocity, vec3 acceleration, float time) {
			return initialVelocity + (acceleration*time);
		}

		vec3 Physics::updateDisplacement(vec3 initialVelocity, vec3 acceleration, float time) {
			return (initialVelocity*time) + (0.5f*acceleration*time*time);
		}

		void Physics::explicitEuler(vec3& position, vec3& velocity, const vec3 acceleration, const float dt) {
			vec3 newvelocity = velocity + (acceleration * dt);
			vec3 displacement = updateDisplacement(newvelocity, acceleration, dt);
			position += displacement;
			velocity = newvelocity;
		}

		void Physics::implicitEuler(vec3& position, vec3& velocity, const vec3 acceleration, const float dt) {
			
		}

		void Physics::semiImplicitEuler(vec3& position, vec3& velocity, const vec3 acceleration, const float dt) {
			
		}

	}
}
