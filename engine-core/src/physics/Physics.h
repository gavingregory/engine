#pragma once

#include <glm/glm.hpp>

namespace engine {
	namespace physics {

		class Physics
		{
		public:
			Physics();
			virtual ~Physics();
			static glm::vec3 displacement(glm::vec3 initialVelocity, glm::vec3 acceleration, float time);
			static glm::vec3 displacementOther(glm::vec3 initialVelocity, glm::vec3 acceleration, float time);
		};

	}
}

