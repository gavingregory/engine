#pragma once

#include <glm/glm.hpp>
#include "../physics/Physics.h"	
#include "RenderObject.h"

namespace engine {
	namespace graphics {
		using namespace glm;
		using namespace engine::physics;
		
		class Entity;
		class PhysicsObject
		{
			friend class Entity;
		public:
			PhysicsObject(vec3 position, vec3 velocity, vec3 acceleration);
			PhysicsObject(vec3 position, vec3 velocity, vec3 acceleration, RenderObject* renderObject);
			virtual ~PhysicsObject();
			void update(float msec);
			void applyForce(vec3 velocity);
		private:
			inline void updateRenderObject();
			vec3 m_Position;
			vec3 m_Velocity;
			vec3 m_Acceleration;
			RenderObject* m_RenderObject;
		};

	}
}