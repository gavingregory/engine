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

		vec3 Physics::semiImplicitEulerIntegration(vec3 initialVelocity, vec3 initialAcceleration, float dt) {
			return vec3(0);
		}

	}
}
