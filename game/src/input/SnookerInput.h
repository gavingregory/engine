#pragma once
#include "../../../engine-core/src/graphics/PhysicsObject.h"
#include "../../../engine-core/src/input/InputHandler.h"
#include "../../../engine-core/src/graphics/Window.h"
#include "../../../engine-core/src/graphics/Camera.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>


#define MAX_KEYS 1024

class SnookerInput : public InputHandler
{
public:
	SnookerInput();
	virtual ~SnookerInput();
	void handleInput(float msec) override;
	inline void setCueBall(engine::graphics::PhysicsObject* cueBall) { m_CueBall = cueBall; }
private:
	bool m_KeysHeld[MAX_KEYS];
	engine::graphics::PhysicsObject* m_CueBall;
};

