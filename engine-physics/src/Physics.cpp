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
		else if (CollisionPlane* derived1 = dynamic_cast<CollisionPlane*>(c1)) {
			return handleCirclePlane(vel0, m0, derived0, pos0, vel1, m1, derived1, pos1, coeffElasticity);
		}
	}
	else if (CollisionPlane* derived0 = dynamic_cast<CollisionPlane*>(c0)) {
		if (CollisionCircle* derived1 = dynamic_cast<CollisionCircle*>(c1)) {
			return handleCirclePlane(vel0, m0, derived1, pos0, vel1, m1, derived0, pos1, coeffElasticity);
		}
		else if (CollisionPlane* derived1 = dynamic_cast<CollisionPlane*>(c1)) {
			return false; // don't need to worry about plane/plane collisions
		}
	}
	return false;
}

bool Physics::handleCircleCircle(vec3& vel0, float m0, CollisionCircle* left, vec3& pos0, vec3& vel1, float m1, CollisionCircle* right, vec3& pos1, float coeffElasticity) {
	if (left == nullptr || right == nullptr) return false;
	float distance = glm::distance(*left->getPositionPtr(), *right->getPositionPtr());
	if (distance < left->get_radius() + right->get_radius()) {
		// calculate p (penetration depth)
		//float p = c0->get_radius() + c1->get_radius() - distance;

		// calculate N (collision normal)
		vec3 N = glm::normalize(glm::abs(left->getPosition() - right->getPosition()));

		// calculate P (point of collision)
		//vec3 P = c0->getPosition() - N * (c1->get_radius() - p);

		// NEW STUFF 

		float mabbefore = glm::length((vel0 * m0) + (vel1 * m1));

		vec3 vAB = vel0 + vel1;

		float vN = glm::dot(vAB, N);

		float J = (-(1 + coeffElasticity)* vN) / (dot(N, N) * (m0 + m1));

		vel0 = DAMPING_FACTOR * (vel0 + ((J*m0) * N));
		vel1 = DAMPING_FACTOR * (vel1 - ((J*m1) * N));

		// clamp
		if (glm::length(vel0) > 0.4f) vel0 = glm::normalize(vel0) * 0.1f;
		if (glm::length(vel1) > 0.4f) vel1 = glm::normalize(vel1) * 0.1f;

		float mabafter = glm::length((vel0 * m0) + (vel1 * m1));
		if (mabbefore < mabafter) {
			std::cout << "before: " << mabbefore;
			std::cout << ", after: " << mabafter << std::endl;
		}
		return true;
	}
	return false;
}

bool Physics::handleCirclePlane(vec3& vel0, float m0, CollisionCircle* left, vec3& pos0, vec3& vel1, float m1, CollisionPlane* right, vec3& pos1, float coeffElasticity) {
	
	vec3 N = right->getNormal();
	vec3 D = right->getDistance();

	float distance = glm::dot(left->getPosition() - D, N);
	if (distance < left->get_radius()) {

		float mabbefore = glm::length((vel0 * m0) + (vel1 * m1));

		vec3 vAB = vel0 + vel1;

		float vN = glm::dot(vAB, N);

		float J = (-(1 + coeffElasticity)* vN) / (dot(N, N) * (m0 + m1));

		vel1 = DAMPING_FACTOR * (vel1 - ((J*m1) * N));
		vel0 = DAMPING_FACTOR * (vel0 + ((J*m0) * N));

		float mabafter = glm::length((vel0 * m0) + (vel1 * m1));
		if (mabbefore < mabafter) {
			std::cout << "before: " << mabbefore;
			std::cout << ", after: " << mabafter << std::endl;
		}
		return true;
	}
	return false;
}
