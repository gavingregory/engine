#pragma once

#include "../../../engine-core/src/graphics/Entity.h"
#include "../../../engine-core/src/graphics/Window.h"

class TableEntity : engine::graphics::Entity
{
public:
	TableEntity();
	TableEntity(glm::vec3 position, glm::vec3 velocity, glm::vec3 acceleration, RenderObject o, string name);
	virtual ~TableEntity();
	void update(float msec) override;
};

