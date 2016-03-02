#include "Physics.h"

Physics::Physics() {}
Physics::~Physics() {}

vec3 Physics::updateVelocity(vec3 initialVelocity, vec3 acceleration, float dt) {
	return initialVelocity + (acceleration*dt);
}

vec3 Physics::updateDisplacement(vec3 initialVelocity, vec3 acceleration, float dt) {
	return (initialVelocity*dt) + (0.5f*acceleration*dt*dt);
}

void Physics::explicitEuler(vec3& position, vec3& velocity, const vec3 acceleration, const float dt) {
	vec3 newvelocity = velocity + (acceleration * dt);
	vec3 displacement = updateDisplacement(newvelocity, acceleration, dt);
	position += displacement;
	velocity = newvelocity;
}

void Physics::implicitEuler(vec3& position, vec3& velocity, const vec3 acceleration, const float dt) {
	velocity = updateVelocity(velocity, acceleration, dt);
	position += updateDisplacement(velocity, acceleration, dt) + (velocity * dt);
}

void Physics::semiImplicitEuler(vec3& position, vec3& velocity, const vec3 acceleration, vec3& displacement, const float dt) {
	velocity = updateVelocity(velocity, acceleration, dt);
	displacement = updateDisplacement(velocity, acceleration, dt);
	position += displacement;
}

bool Physics::detectCollision(vec3& vel0, float m0, CollisionShape* c0, vec3& pos0, vec3& vel1, float m1, CollisionShape* c1, vec3& pos1, float coeffElasticity) {
	
	if (CollisionCircle* derived0 = dynamic_cast<CollisionCircle*>(c0)) {
		if (CollisionCircle* derived1 = dynamic_cast<CollisionCircle*>(c1)) {
			return handleCircleCircle(vel0, m0, derived0, pos0, vel1, m1, derived1, pos1, coeffElasticity);
		}
		else if (CollisionRectangle* derived1 = dynamic_cast<CollisionRectangle*>(c1)) {
			return handleCircleRect(vel0, m0, derived0, pos0, vel1, m1, derived1, pos1, coeffElasticity);
		}
	}
	else if (CollisionRectangle* derived0 = dynamic_cast<CollisionRectangle*>(c0)) {
		if (CollisionCircle* derived1 = dynamic_cast<CollisionCircle*>(c1)) {
			return handleCircleRect(vel0, m0, derived1, pos0, vel1, m1, derived0, pos1, coeffElasticity);
		}
		else if (CollisionRectangle* derived1 = dynamic_cast<CollisionRectangle*>(c1)) {
			return handleRectRect(vel0, m0, derived0, pos0, vel1, m1, derived1, pos1, coeffElasticity);
		}
	}
	return false;
}

bool Physics::handleCircleCircle(vec3& vel0, float m0, CollisionCircle* left, vec3& pos0, vec3& vel1, float m1, CollisionCircle* right, vec3& pos1, float coeffElasticity) {
	if (left == nullptr || right == nullptr) return false;
	float distance = glm::distance(*left->getPositionPtr(), *right->getPositionPtr());
	if (distance < left->get_radius() + right->get_radius()) {
		std::cout << "circle/circle collision detected" << std::endl;

		// calculate p (penetration depth)
		//float p = c0->get_radius() + c1->get_radius() - distance;

		// calculate N (collision normal)
		vec3 N = glm::normalize(glm::abs(left->getPosition() - right->getPosition()));

		// calculate P (point of collision)
		//vec3 P = c0->getPosition() - N * (c1->get_radius() - p);

		// NEW STUFF 

		vec3 mab = (vel0 * m0) + (vel1 * m1);
		std::cout << mab.x << ", " << mab.y << ", " << mab.z << ", " << glm::length(mab) << " : ";

		vec3 vAB = vel0 + vel1;

		float vN = glm::dot(vAB, N);

		float J = (-(1 + coeffElasticity)* vN) / (dot(N, N) * (m0 + m1));

		vel0 = vel0 + ((J*m0) * N);
		vel1 = vel1 - ((J*m1) * N);

		mab = (vel0 * m0) + (vel1 * m1);
		std::cout << mab.x << ", " << mab.y << ", " << mab.z << ", " << glm::length(mab) << std::endl;
		return true;
	}
	return false;
}


bool Physics::handleCircleRect(vec3& vel0, float m0, CollisionCircle* left, vec3& pos0, vec3& vel1, float m1, CollisionRectangle* right, vec3& pos1, float coeffElasticity) {
	if (left == nullptr || right == nullptr) return false;

	float r0_l = left->getPosition().x - left->get_radius();
	float r0_r = left->getPosition().x + left->get_radius();
	float r0_t = left->getPosition().y + left->get_radius();
	float r0_b = left->getPosition().y - left->get_radius();
	float r1_l = right->getPosition().x - (right->getWidth() / 2);
	float r1_r = right->getPosition().x + (right->getWidth() / 2);
	float r1_t = right->getPosition().y + (right->getHeight() / 2);
	float r1_b = right->getPosition().y - (right->getHeight() / 2);

	// first check for bounding box collision. If this occurs, we perform a second check to check if an actual
	// collision has occurred.
	if (!(r1_l > r0_r || r1_r < r0_l || r1_t > r0_b || r1_b < r0_t)) {
		// bounding box collision! Perform detailed checked:

		// find closest point to the circle within the rectangle
		float closestX = glm::clamp(left->getPosition().x, r1_l, r1_r);
		float closestY = glm::clamp(left->getPosition().y, r1_t, r1_b);

		// calculate the distance between the circle's center and this closest point
		float distanceX = left->getPosition().x - closestX;
		float distanceY = left->getPosition().y - closestY;

		// If the distance is less than the circle's radius, an intersection occurs
		float distanceSquared = (distanceX * distanceX) + (distanceY * distanceY);
		if (distanceSquared < (left->get_radius() * left->get_radius())) {
			// collision for defo
			std::cout << "circle rect collision for defo" << std::endl;
			return true;
		}
	}
	return false;
}

bool Physics::handleRectRect(vec3& vel0, float m0, CollisionRectangle* c0, vec3& pos0, vec3& vel1, float m1, CollisionRectangle* c1, vec3& pos1, float coeffElasticity) {
	return false;
}