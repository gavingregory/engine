#include "PhysicsObject.h"



namespace engine {
	namespace graphics {
		using namespace glm;
		using namespace engine::physics;
		
		PhysicsObject::PhysicsObject(vec3 position, vec3 velocity, vec3 acceleration)
			: m_Position(position), m_Velocity(velocity), m_Acceleration(acceleration), m_RenderObject(nullptr) {
			updateRenderObject();
		}

		PhysicsObject::PhysicsObject(vec3 position, vec3 velocity, vec3 acceleration, RenderObject* renderObject)
			: m_Position(position), m_Velocity(velocity), m_Acceleration(acceleration), m_RenderObject(renderObject) {
			updateRenderObject();
		}

		void PhysicsObject::update(float msec) {
			Physics::semiImplicitEuler(m_Position, m_Velocity, m_Acceleration, msec);
			// stop an object
			if (m_Velocity.x < 0.00001f && m_Velocity.y < 0.00001f && m_Velocity.z < 0.00001f) {
				m_Velocity.x = 0; m_Velocity.y = 0; m_Velocity.z = 0; m_Acceleration.x = 0; m_Acceleration.y = 0; m_Acceleration.z = 0;
			}
			updateRenderObject();
		}

		void PhysicsObject::updateRenderObject() {
			m_RenderObject->SetModelMatrix(glm::translate(m_Position));
		}

		void PhysicsObject::applyForce(vec3 velocity, vec3 acceleration) {
			m_Velocity += velocity;
			m_Acceleration += acceleration;
		}

		PhysicsObject::~PhysicsObject() {}
	}
}

