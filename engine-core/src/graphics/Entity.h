#pragma once

#include <glm/glm.hpp>
#include "RenderObject.h"
#include "Renderer.h"
#include "../physics/Physics.h"

namespace engine {
	namespace graphics {
		using namespace glm;
		using namespace engine::physics;

		class Entity
		{
		public:
			Entity();
			Entity(vec3 position, vec3 velocity, vec3 acceleration, RenderObject o);
			virtual ~Entity();

			inline vec3* getPosition() const { return position; }
			inline vec3* getAcceleration() const { return acceleration; }
			inline vec3* getVelocity() const { return velocity; }
			inline RenderObject getRenderObject() const { return renderObject; }

			virtual void update(float dt);
			virtual void render(Renderer* renderer);

		protected:
			vec3* position;
			vec3* acceleration;
			vec3* velocity;
			RenderObject renderObject;
		};

	}
}