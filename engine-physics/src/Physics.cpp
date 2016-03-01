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

bool Physics::handleCollision(vec3& vel0, float m0, CollisionCircle* c0, vec3& pos0, vec3& vel1, float m1, CollisionCircle* c1, vec3& pos1, float coeffElasticity) {
	float distance;
	if (!detectCollision(c0, c1, distance)) return false;
	std::cout << "collision detected" << std::endl;

	// calculate p (penetration depth)
	//float p = c0->get_radius() + c1->get_radius() - distance;

	// calculate N (collision normal)
	vec3 N = glm::normalize(glm::abs(c0->getPosition() - c1->getPosition()));

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

bool Physics::detectCollision(CollisionCircle* left, CollisionCircle* right, float& distance) {
	if (left == nullptr || right == nullptr) return false;
	distance = glm::distance(*left->getPositionPtr(), *right->getPositionPtr());
	if (distance < left->get_radius() || distance < right->get_radius())
		return true;
	return false;
}
