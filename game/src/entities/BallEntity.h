#pragma once

#include "../../../engine-common/src/graphics/Entity.h"
#include "../../../engine-common/src/graphics/Window.h"

/**
 * Ball Entity Parameters (a struct of params used when constructing ball entities)
 */
struct BallEntityParams {
	vec3 position;
	vec3 velocity;
	vec3 acceleration;
	float rotation;
	float mass;
	Mesh* mesh;
	Shader* shader;
	string name;
	float radius;
};

class BallEntity : public Entity
{
public:
	BallEntity(BallEntityParams params, RenderObject* ro, PhysicsObject* po, CollisionCircle* c);
	virtual ~BallEntity();
};
