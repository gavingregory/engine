#pragma once

#include "../../../engine-core/src/graphics/Entity.h"
#include "../../../engine-core/src/graphics/Window.h"

class Ball : engine::graphics::Entity
{
public:
	Ball();
	Ball(glm::vec3 position, glm::vec3 velocity, glm::vec3 acceleration, RenderObject o);
	virtual ~Ball();
	void update(float msec) override;
};
