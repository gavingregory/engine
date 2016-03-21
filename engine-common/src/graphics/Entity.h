#pragma once

#include <glm/glm.hpp>
#include "RenderObject.h"
#include "PhysicsObject.h"
#include "Renderer.h"
#include "../../../engine-physics/src/Physics.h"

using std::vector;

struct EntityParams {
	vec3 position;
	vec3 velocity;
	vec3 acceleration;
	float rotation;
	float mass;
	Mesh* mesh;
	Shader* shader;
	string name;
};

class Entity
{
public:
	Entity(EntityParams params, RenderObject* ro, PhysicsObject* po);
	virtual ~Entity();

	inline vec3 getPosition() const { return m_PhysicsObject->m_Position; }
	inline vec3 getAcceleration() const { return m_PhysicsObject->m_Acceleration; }
	inline vec3 getVelocity() const { return m_PhysicsObject->m_Velocity; }
	inline RenderObject* getRenderObject() const { return m_RenderObject; }
	inline PhysicsObject* getPhysicsObject() const { return m_PhysicsObject; }
	inline string getName() const { return m_Name; }
	inline void setCollisionShape(CollisionShape* collisionShape) {
		getPhysicsObject()->m_CollisionShape = collisionShape;
		// add this shape to colliders if it has a collision shape
		if (collisionShape != nullptr) {
			CollidingEntities.push_back(this);	
		}
	}

	// function gets called on a collision with another entity
	virtual void collisionEvent(Entity* other) { }

	virtual void update(float dt);
	virtual void render(Renderer* renderer);

	void addChild(Entity* e);
	vector<Entity*>* getChildren() { return &children; }
	static vector<Entity*> CollidingEntities;
protected:
	string m_Name;
	RenderObject* m_RenderObject;
	PhysicsObject* m_PhysicsObject;
	Entity* parent;
	vector<Entity*> children;
};