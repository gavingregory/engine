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
			static vec3 displacement(vec3 initialVelocity, vec3 acceleration, float time);
			static vec3 displacementOther(vec3 initialVelocity, vec3 acceleration, float time);
		};

	}
}

