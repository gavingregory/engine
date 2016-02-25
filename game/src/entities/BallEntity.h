#pragma once

#include "../../../engine-core/src/graphics/Entity.h"
#include "../../../engine-core/src/graphics/Window.h"

class BallEntity : engine::graphics::Entity
{
public:
	BallEntity(glm::vec3 position, glm::vec3 velocity, glm::vec3 acceleration, Mesh* mesh, Shader* shader, string name);
	virtual ~BallEntity();
	void update(float msec) override;
};
