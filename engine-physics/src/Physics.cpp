#include "Physics.h"

namespace engine {
	namespace physics {

		Physics::Physics() {}
		Physics::~Physics() {}

		vec3 Physics::updateVelocity(vec3 initialVelocity, vec3 acceleration, float time) {
			return initialVelocity + (acceleration*time);
		}

		vec3 Physics::updateDisplacement(vec3 initialVelocity, vec3 acceleration, float time) {
			return (initialVelocity*time) + (0.5f*acceleration*time*time);
		}

		void Physics::explicitEuler(vec3& position, vec3& velocity, const vec3 acceleration, const float dt) {
			vec3 newvelocity = velocity + (acceleration * dt);
			vec3 displacement = updateDisplacement(newvelocity, acceleration, dt);
			position += displacement;
			velocity = newvelocity;

			
		}

		void Physics::implicitEuler(vec3& position, vec3& velocity, const vec3 acceleration, const float dt) {
			velocity = velocity + acceleration * dt;
			position += updateDisplacement(velocity, acceleration, dt) + (velocity * dt);
		}

		void Physics::semiImplicitEuler(vec3& position, vec3& velocity, const vec3 acceleration, const float dt) {
			vec3 newvelocity = velocity + (acceleration * dt);
			vec3 displacement = updateDisplacement(velocity, acceleration, dt);
			vec3 newdisplacement = displacement + (newvelocity * dt);
			position += newdisplacement;
			velocity = newvelocity;
		}

		void Physics::handleCollision(vec3& vel0, float m0, Circle* c0, vec3& pos0, vec3& vel1, float m1, Circle* c1, vec3& pos1, float coeffElasticity) {
			float distance;
			if (!detectCollision(c0, c1, distance)) return;
			std::cout << "collision detected" << std::endl;
			// calculate p (penetration depth)
			float p = c0->get_radius() + c1->get_radius() - distance;

			// calculate N (collision normal)
			vec3 N = glm::normalize(glm::abs(c0->getPosition() - c1->getPosition()));

			// calculate P (point of collision)
			vec3 P = c0->getPosition() - N * (c1->get_radius() - p);

			pos0 += -(N*(p));


			vel0 = vec3(0);
			vel1 = vec3(0);

		}

		bool Physics::detectCollision(Circle* left, Circle* right, float& distance) {
			if (left == nullptr || right == nullptr) return false;
			distance = glm::distance(*left->getPositionPtr(), *right->getPositionPtr());
			if (distance < left->get_radius() || distance < right->get_radius())
				return true;
			return false;
		}

		//void Physics::resolveCollision(vec3& v0, float m0, vec3 pos0, vec3& v1, float m1, vec3 pos1, float dt, float coeffElasticity) {
		//
		//	// Vab = Va + Vb
		//	vec3 Vab = glm::cross(v0, v1);
		//
		//	// N // WRONG
		//	vec3 N = glm::abs(pos1 - pos0);
		//
		//	// velocity in direction of the normal (Vn)
		//	float Vn = glm::dot(Vab, N);
		//
		//	// J
		//	float J = (-(1 + coeffElasticity) * Vn) / (glm::dot(N,N) * (m0 + (1.0f / m1)));
		//
		//	v0 = v0 + (J*m0 * N);
		//	v1 = v1 + (J*m1 * N);
		//
		//	std::cout << "something";
		//
		//	//float xDistance = (second.x - first.x);
		//	//float yDistance = (second.y - first.y);
		//	//float zDistance = (second.z - first.z);
		//	//
		//	//vec3 normalVector = vec3(xDistance, yDistance, zDistance);
		//	//normalVector = normalize(normalVector);
		//	//
		//	//vec3 tangentVector = vec3(normalVector.y * -1, normalVector.x, normalVector.z);
		//	//
		//	//// create ball scalar normal direction.
		//	//float ball1scalarNormal = dot(normalVector, first);
		//	//float ball2scalarNormal = dot(normalVector, second);
		//	//
		//	//// create scalar velocity in the tagential direction.
		//	//float ball1scalarTangential = dot(tangentVector, first);
		//	//float ball2scalarTangential = dot(tangentVector, second);
		//	//
		//	//
		//	//float ball1ScalarNormalAfter = (ball1scalarNormal * (firstMass - secondMass) +
		//	//	2 * secondMass * ball2scalarNormal) / (firstMass + secondMass);
		//	//float ball2ScalarNormalAfter = (ball2scalarNormal * (secondMass - firstMass) +
		//	//	2 * firstMass * ball1scalarNormal) / (firstMass + secondMass);
		//	//
		//	//vec3 ball1scalarNormalAfter_vector = normalVector * ball1ScalarNormalAfter;
		//	//vec3 ball2scalarNormalAfter_vector = normalVector * ball2ScalarNormalAfter;
		//	//
		//	//vec3 ball1ScalarNormalVector = tangentVector * ball1scalarTangential;
		//	//vec3 ball2ScalarNormalVector = tangentVector * ball2scalarTangential;
		//	//
		//	//first = ball1ScalarNormalVector + ball1scalarNormalAfter_vector;
		//	//second = ball2ScalarNormalVector + ball2scalarNormalAfter_vector;
		//}

	}
}
