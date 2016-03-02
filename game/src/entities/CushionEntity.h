#pragma once

#include "../../../engine-common/src/graphics/Entity.h"
#include "../../../engine-common/src/graphics/Window.h"
#include <glm/glm.hpp>

using glm::vec3;


struct CushionEntityParams {
	vec3 position;
	vec3 velocity;
	vec3 acceleration;
	Mesh* mesh;
	Shader* shader;
	string name;
	float width;
	float height;
};

class CushionEntity : public Entity
{
public:
	CushionEntity(CushionEntityParams params, RenderObject* ro, PhysicsObject* po, CollisionRectangle* r);
	virtual ~CushionEntity();
};

