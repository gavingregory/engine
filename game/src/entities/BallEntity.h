#pragma once

#include "../../../engine-common/src/graphics/Entity.h"
#include "../../../engine-common/src/graphics/Window.h"

using namespace engine;
using namespace graphics;

class BallEntity : public Entity
{
public:
	BallEntity(glm::vec3 position, glm::vec3 velocity, glm::vec3 acceleration, Mesh* mesh, Shader* shader, float radius, string name);
	virtual ~BallEntity();
};
