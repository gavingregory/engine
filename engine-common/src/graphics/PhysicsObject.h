#pragma once

#include <glm/glm.hpp>
#include "../../../engine-physics/src/Physics.h"
#include "../../../engine-physics/src/collision/Shape.h"
#include "../../../engine-physics/src/collision/CollisionCircle.h"
#include "RenderObject.h"

#define DAMPING_FACTOR 0.999f

using glm::vec3;
using std::map;

struct PhysicsObjectParams {
	vec3 position;
	vec3 velocity;
	vec3 acceleration;
	RenderObject* renderObject;
	Shape* collisionShape;
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
	inline Shape* getCollisionShape() const { return m_CollisionShape; }
	inline void setCollisionShape(Shape* collisionShape) {
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
	void collide(PhysicsObject*);
	void noCollide(PhysicsObject*);
	bool isColliding(PhysicsObject*);
	static vector<PhysicsObject*> m_Colliders;
private:
	inline void updateRenderObject();
	float m_Rotation;
	vec3 m_Position;
	vec3 m_Velocity;
	vec3 m_Acceleration;
	vec3 m_PreviousDisplacement;
	map<PhysicsObject*, bool> m_Collisions;
	RenderObject* m_RenderObject;
	Shape* m_CollisionShape;
};