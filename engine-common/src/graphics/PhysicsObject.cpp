#include "PhysicsObject.h"

vector<PhysicsObject*> PhysicsObject::m_Colliders;

PhysicsObject::PhysicsObject(PhysicsObjectParams params)
	: m_Position(params.position), m_Velocity(params.velocity), m_Acceleration(params.acceleration), m_RenderObject(params.renderObject), m_CollisionShape(params.collisionShape) {
	updateRenderObject();
	// add this shape to colliders if it has a collision shape
	if (m_CollisionShape != nullptr) {
		cout << "adding a collision object " << endl; m_Colliders.push_back(this);
	}
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

PhysicsObject::~PhysicsObject() {
	if (m_CollisionShape) delete m_CollisionShape;
}
