#include "PhysicsObject.h"
namespace engine {
	namespace graphics {
		using namespace glm;
		using namespace engine::physics;
		
		PhysicsObject::PhysicsObject(vec3 position, vec3 velocity, vec3 acceleration)
			: m_Position(position), m_Velocity(velocity), m_Acceleration(acceleration), m_RenderObject(nullptr), m_CollisionShape(nullptr) {
			updateRenderObject();
		}

		PhysicsObject::PhysicsObject(vec3 position, vec3 velocity, vec3 acceleration, RenderObject* renderObject, Shape* collisionShape)
			: m_Position(position), m_Velocity(velocity), m_Acceleration(acceleration), m_RenderObject(renderObject), m_CollisionShape(collisionShape) {
			updateRenderObject();
		}

		void PhysicsObject::update(float msec) {
			Physics::semiImplicitEuler(m_Position, m_Velocity, m_Acceleration, m_PreviousDisplacement, msec);
			m_Velocity *= DAMPING_FACTOR;
			// stop an object
			if (abs(m_Velocity.x) < 0.00001f && abs(m_Velocity.y) < 0.00001f && abs(m_Velocity.z) < 0.00001f) {
				m_Velocity.x = 0; m_Velocity.y = 0; m_Velocity.z = 0;
			}
			updateRenderObject();
		}

		void PhysicsObject::updateRenderObject() {
			m_RenderObject->SetModelMatrix(glm::translate(m_Position));
		}

		void PhysicsObject::applyForce(vec3 velocity) {
			m_Velocity += velocity;
		}


		void PhysicsObject::collide(PhysicsObject* o) {
			m_Collisions.insert_or_assign(o, true);
		}

		void PhysicsObject::noCollide(PhysicsObject* o) {
			std::map<PhysicsObject*, bool>::iterator it;
			it = m_Collisions.find(o);
			if (it != m_Collisions.end())
				m_Collisions.erase(it);
		}

		bool PhysicsObject::isColliding(PhysicsObject* o) {
			std::map<PhysicsObject*, bool>::iterator it;
			it = m_Collisions.find(o);
			if (it != m_Collisions.end())
				return true;
			return false;
		}

		PhysicsObject::~PhysicsObject() {}
	}
}

