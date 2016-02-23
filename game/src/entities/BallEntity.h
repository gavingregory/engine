#pragma once

#include "../../../engine-core/src/graphics/Entity.h"
#include "../../../engine-core/src/graphics/Window.h"

class BallEntity : engine::graphics::Entity
{
public:
	BallEntity();
	BallEntity(glm::vec3 position, glm::vec3 velocity, glm::vec3 acceleration, RenderObject o, string name, glm::vec4 colour);
	virtual ~BallEntity();
	void update(float msec) override;
};
