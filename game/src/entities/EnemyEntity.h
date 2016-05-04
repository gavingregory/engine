/******************************************************************************
Class:EnemyEntity
Author:Gavin Gregory
Description:A subclass of Entity that represents an Enemy in the game.
*//////////////////////////////////////////////////////////////////////////////

#pragma once

#include "../../../engine-common/src/graphics/Entity.h"
#include "../../../engine-common/src/graphics/Window.h"

#define MAX_WAYPOINTS 4

struct EnemyEntityParams {
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
	bool loopWaypoints;
	b2Vec2 waypoints0;
	b2Vec2 waypoints1;
	b2Vec2 waypoints2;
	b2Vec2 waypoints3;
};

class EnemyEntity : public Entity
{
public:
	EnemyEntity(EnemyEntityParams params, RenderObject* ro);
	virtual ~EnemyEntity();
	bool loopWaypoints = true; //whether we loop through waypoints or not (go back through them in opposite direction!).
	b2Vec2 waypoints[MAX_WAYPOINTS];
	int currentWaypoint = 0;
};
