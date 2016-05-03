/******************************************************************************
Class:PlayerEntity
Author:Gavin Gregory
Description:A subclass of Entity that represents the player in the game.
*//////////////////////////////////////////////////////////////////////////////

#pragma once

#include "../../../engine-common/src/graphics/Entity.h"
#include "../../../engine-common/src/graphics/Window.h"

struct PlayerEntityParams {
	vec3 position;
	vec3 velocity;
	vec3 acceleration;
	float rotation;
	float mass;
	Mesh* mesh;
	Shader* shader;
	string name;
	bool hasPhysics;
	b2BodyDef bodyDef;
	b2PolygonShape shape;
};

class PlayerEntity : public Entity
{
public:
	PlayerEntity(PlayerEntityParams params, RenderObject* ro);
	virtual ~PlayerEntity();
	void rotate(float angleDeg);
	void boost();
};
