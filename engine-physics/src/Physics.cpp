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

		void Physics::resolveCollision(vec3& v1, float m1, vec3& v2, float m2) {


			v1 = ((m1 - m2)*v1 + 2 * m2*v2) / (m1 + m2);
			v2 = ((m2 - m1)*v2 + 2 * m1*v1) / (m1 + m2);


			//float xDistance = (second.x - first.x);
			//float yDistance = (second.y - first.y);
			//float zDistance = (second.z - first.z);
			//
			//vec3 normalVector = vec3(xDistance, yDistance, zDistance);
			//normalVector = normalize(normalVector);
			//
			//vec3 tangentVector = vec3(normalVector.y * -1, normalVector.x, normalVector.z);
			//
			//// create ball scalar normal direction.
			//float ball1scalarNormal = dot(normalVector, first);
			//float ball2scalarNormal = dot(normalVector, second);
			//
			//// create scalar velocity in the tagential direction.
			//float ball1scalarTangential = dot(tangentVector, first);
			//float ball2scalarTangential = dot(tangentVector, second);
			//
			//
			//float ball1ScalarNormalAfter = (ball1scalarNormal * (firstMass - secondMass) +
			//	2 * secondMass * ball2scalarNormal) / (firstMass + secondMass);
			//float ball2ScalarNormalAfter = (ball2scalarNormal * (secondMass - firstMass) +
			//	2 * firstMass * ball1scalarNormal) / (firstMass + secondMass);
			//
			//vec3 ball1scalarNormalAfter_vector = normalVector * ball1ScalarNormalAfter;
			//vec3 ball2scalarNormalAfter_vector = normalVector * ball2ScalarNormalAfter;
			//
			//vec3 ball1ScalarNormalVector = tangentVector * ball1scalarTangential;
			//vec3 ball2ScalarNormalVector = tangentVector * ball2scalarTangential;
			//
			//first = ball1ScalarNormalVector + ball1scalarNormalAfter_vector;
			//second = ball2ScalarNormalVector + ball2scalarNormalAfter_vector;
		}

	}
}
