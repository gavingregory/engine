#pragma once

#include "../../../engine-common/src/graphics/Entity.h"
#include "../../../engine-common/src/graphics/Window.h"
#include <glm/glm.hpp>

using glm::vec3;

/**
* Cushion Entity Parameters (a struct of params used when constructing cushion entities)
*/
struct CushionEntityParams {
	vec3 position;
	vec3 velocity;
	vec3 acceleration;
	float rotation;
	float mass;
	Mesh* mesh;
	Shader* shader;
	string name;
	vec3 normal;
	vec3 distance;
};

class CushionEntity : public Entity
{
public:
	CushionEntity(CushionEntityParams params, RenderObject* ro, PhysicsObject* po, CollisionPlane* r);
	virtual ~CushionEntity();
};

