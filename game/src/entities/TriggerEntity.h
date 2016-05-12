/******************************************************************************
Class:TriggerEntity
Author:Gavin Gregory
Description:A subclass of Entity that represents an Trigger in the game.
*//////////////////////////////////////////////////////////////////////////////

#pragma once

#include "../../../engine-common/src/graphics/Entity.h"
#include "../../../engine-common/src/graphics/Window.h"

#define MAX_WAYPOINTS 4

struct TriggerEntityParams {
	vec3 position;
	vec3 velocity;
	vec3 acceleration;
	float rotation;
	bool rotates;
	float mass;
	Mesh* mesh;
	Shader* shader;
	string name;
	EntityCategory category;
	bool hasPhysics;
	bool isSensor;
	b2BodyDef bodyDef;
	b2PolygonShape shape;
};

class TriggerEntity : public Entity
{
public:
	TriggerEntity(TriggerEntityParams params, RenderObject* ro);
	virtual ~TriggerEntity();
	bool m_LoopWaypoints = true; //whether we loop through waypoints or not (go back through them in opposite direction!).
	int m_NumWaypoints = 2;
	b2Vec2 m_Waypoints[MAX_WAYPOINTS];
	int m_CurrentWaypoint = 0;
	void update(float msec) override;
	bool m_Rotates;
};
