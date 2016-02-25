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
			m_Velocity = Physics::updateVelocity(m_Velocity, m_Acceleration, msec);
			m_Position = Physics::updateDisplacement(m_Velocity, m_Acceleration, msec);
			updateRenderObject();
		}

		void PhysicsObject::updateRenderObject() {
			m_RenderObject->SetModelMatrix(glm::translate(m_Position));
		}

		void PhysicsObject::applyForce(vec3 velocity) {
			m_Velocity *= velocity;
		}

		PhysicsObject::~PhysicsObject() {}
	}
}

