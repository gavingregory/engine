#pragma once

#include "../../../engine-common/src/graphics/Entity.h"
#include "../../../engine-common/src/graphics/Window.h"

struct NodeEntityParams {
	vec3 position;
	vec3 velocity;
	vec3 acceleration;
	float rotation;
	float mass;
	Mesh* mesh;
	Shader* shader;
	string name;
	float radius;
	bool isDynamic;
};

class NodeEntity : public Entity
{
public:
	NodeEntity(NodeEntityParams params, RenderObject* ro);
	virtual ~NodeEntity();
};
