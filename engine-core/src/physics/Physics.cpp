#include "Physics.h"

namespace engine {
	namespace physics {

		Physics::Physics() {}
		Physics::~Physics() {}

		glm::vec3 Physics::displacement(glm::vec3 initialVelocity, glm::vec3 acceleration, float time) {
			return initialVelocity + (acceleration*time);
		}

		glm::vec3 Physics::displacementOther(glm::vec3 initialVelocity, glm::vec3 acceleration, float time) {
			return (initialVelocity*time) + (0.5f*acceleration*time*time);
		}

	}
}
