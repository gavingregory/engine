#pragma once

#include <glm/glm.hpp>
#include "../../../engine-physics/src/Physics.h"
#include "../../../engine-physics/src/collision/Shape.h"
#include "../../../engine-physics/src/collision/Circle.h"
#include "RenderObject.h"

#define DAMPING_FACTOR 0.999f

namespace engine {
	namespace graphics {
		using namespace glm;
		using namespace engine::physics;
		
		class Entity;
		class PhysicsObject
		{
			friend class Entity;
			friend class GameManager;
		public:
			PhysicsObject(vec3 position, vec3 velocity, vec3 acceleration);
			PhysicsObject(vec3 position, vec3 velocity, vec3 acceleration, RenderObject* renderObject, Shape* collisionShape);
			virtual ~PhysicsObject();
			void update(float msec);
			void applyForce(vec3 velocity);
			inline Shape* getCollisionShape() const { return m_CollisionShape; }
			inline void setCollisionShape(Shape* collisionShape) { m_CollisionShape = collisionShape;  }
			inline vec3* getPositionPtr() { return &m_Position; }
			inline vec3* getVelocityPtr() { return &m_Velocity; }
			inline vec3 getPosition() { return m_Position; }
			inline vec3 getVelocity() { return m_Velocity; }
			inline void setPosition(vec3 position) { m_Position = position; }
		private:
			inline void updateRenderObject();
			vec3 m_Position;
			vec3 m_Velocity;
			vec3 m_Acceleration;
			vec3 m_PreviousDisplacement;
			RenderObject* m_RenderObject;
			Shape* m_CollisionShape;
		};

	}
}