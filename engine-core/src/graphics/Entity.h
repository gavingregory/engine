#pragma once

#include <glm/glm.hpp>
#include "renderers/RenderObject.h"

namespace engine {
	namespace graphics {
		using namespace glm;

		class Entity
		{
		public:
			Entity();
			Entity(vec3 position, vec3 velocity, vec3 acceleration);
			virtual ~Entity();

			inline vec3* getPosition() const { return position; }
			inline vec3* getAcceleration() const { return acceleration; }
			inline vec3* getVelocity() const { return velocity; }

		private:
			vec3* position;
			vec3* acceleration;
			vec3* velocity;
			RenderObject* renderObject;
		};

	}
}