#pragma once

#include <glm/glm.hpp>
#include "../../../engine-physics/src/Physics.h"
#include "../../../engine-physics/src/collision/CollisionShape.h"
#include "../../../engine-physics/src/collision/CollisionCircle.h"
#include "RenderObject.h"

#define DAMPING_FACTOR 0.999f

using glm::vec3;
using std::map;

struct PhysicsObjectParams {
	vec3 position;
	vec3 velocity;
	vec3 acceleration;
	float rotation;
	float mass;
	RenderObject* renderObject;
	CollisionShape* collisionShape;
};

class Entity;
class PhysicsObject
{
	friend class Entity;
	friend class GameManager;
public:
	PhysicsObject(PhysicsObjectParams params);
	virtual ~PhysicsObject();
	void update(float msec);
	void applyForce(vec3 velocity);
	inline CollisionShape* getCollisionShape() const { return m_CollisionShape; }
	inline void setCollisionShape(CollisionShape* collisionShape) {
		m_CollisionShape = collisionShape;
		// add this shape to colliders if it has a collision shape
		if (m_CollisionShape != nullptr) {
			cout << "adding a collision object " << endl; m_Colliders.push_back(this);
		}
	}
	inline vec3* getPositionPtr() { return &m_Position; }
	inline vec3* getVelocityPtr() { return &m_Velocity; }
	inline vec3 getPosition() { return m_Position; }
	inline vec3 getVelocity() { return m_Velocity; }
	inline float getRotation() { return m_Rotation; }
	inline void setPosition(vec3 position) { m_Position = position; }
	inline void setRotation(float rotation) { m_Rotation = rotation; }
	inline float getMass() const { return m_Mass; }
	void collide(PhysicsObject*);
	void noCollide(PhysicsObject*);
	bool isColliding(PhysicsObject*);
	static vector<PhysicsObject*> m_Colliders;
private:
	inline void updateRenderObject();
	float m_Rotation;
	float m_Mass;
	vec3 m_Position;
	vec3 m_Velocity;
	vec3 m_Acceleration;
	vec3 m_PreviousDisplacement;
	map<PhysicsObject*, bool> m_Collisions;
	RenderObject* m_RenderObject;
	CollisionShape* m_CollisionShape;
};