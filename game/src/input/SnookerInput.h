#pragma once
#include "../../../engine-core/src/input/InputHandler.h"
#include "../../../engine-core/src/graphics/Window.h"
#include "../../../engine-core/src/graphics/Camera.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>

class SnookerInput : public InputHandler
{
public:
	SnookerInput();
	virtual ~SnookerInput();
	void handleInput(float msec) override;
};

