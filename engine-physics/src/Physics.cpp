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

		void Physics::resolveCollision(vec3* firstBall, float firstMass, vec3* secondBall, float secondMass) {
			//float newVelX1 = (firstBall->x * (firstMass - secondMass) + (2 * secondMass * secondBall->x)) / (firstMass + secondMass);
			//float newVelY1 = (firstBall->y * (firstMass - secondMass) + (2 * secondMass * secondBall->y)) / (firstMass + secondMass);
			//float newVelZ1 = (firstBall->z * (firstMass - secondMass) + (2 * secondMass * secondBall->z)) / (firstMass + secondMass);
			//float newVelX2 = (secondBall->x * (secondMass - firstMass) + (2 * firstMass * firstBall->x)) / (firstMass + secondMass);
			//float newVelY2 = (secondBall->y * (secondMass - firstMass) + (2 * firstMass * firstBall->y)) / (firstMass + secondMass);
			//float newVelZ2 = (secondBall->z * (secondMass - firstMass) + (2 * firstMass * firstBall->z)) / (firstMass + secondMass);
			//firstBall->x = newVelX1;
			//firstBall->y = newVelY1;
			//firstBall->z = newVelZ1;
			//secondBall->x = newVelX2;
			//secondBall->y = newVelY2;
			//secondBall->z = newVelZ2;
			firstBall->x = 0.0f;
			firstBall->y = 0.0f;
			firstBall->z = 0.0f;
			secondBall->x = 0.0f;
			secondBall->y = 0.0f;
			secondBall->z = 0.0f;
		}

	}
}
