/******************************************************************************
Class:Entity
Author:Gavin Gregory
Description:All objects in the game world are Entities. Entities have member variables
such as render objects and physics objects to represent their different properties.
*//////////////////////////////////////////////////////////////////////////////

#pragma once

#include <glm/glm.hpp>
#include <box2d/Box2D.h>
#include "RenderObject.h"
#include "Renderer.h"
#include "../../../engine-audio/src/Audio.h"
#include "../../../engine-physics/src/Physics.h"

using std::vector;

enum EntityCategory {
	EC_PLAYER = 0,
	EC_PLATFORM,
	EC_ENEMY,
	EC_EXIT,
	EC_NONE
};

struct EntityParams {
	vec3 position;
	vec3 velocity;
	vec3 acceleration;
	float rotation;
	float mass;
	Mesh* mesh;
	Shader* shader;
	string name;
	EntityCategory category;
	bool hasPhysics;
	b2BodyDef bodyDef;
	b2PolygonShape shape;
};

class Entity
{
public:
	Entity(EntityParams params, RenderObject* ro);
	virtual ~Entity();
	inline vec3 getPosition() const { return vec3(m_PhysicsObject->GetPosition().x, m_PhysicsObject->GetPosition().y, 0); }
	inline vec3 getVelocity() const { return glm::vec3(m_PhysicsObject->GetLinearVelocity().x, m_PhysicsObject->GetLinearVelocity().y, 0); }
	inline RenderObject* getRenderObject() const { return m_RenderObject; }
	inline b2Body* getPhysicsObject() const { return m_PhysicsObject; }
	inline string getName() const { return m_Name; }
	inline map<string, ISoundSource*>* getSounds() { return &m_Sounds; }
	inline EntityCategory getCategory() { return m_Category; }

	virtual void update(float dt);
	virtual void render(Renderer* renderer);

	void addChild(Entity* e);
	vector<Entity*>* getChildren() { return &children; }

protected:
	string m_Name;
	RenderObject* m_RenderObject;
	b2Body* m_PhysicsObject;
	Entity* parent;
	vector<Entity*> children;
	map<string, ISoundSource*> m_Sounds;
	EntityCategory m_Category;
};