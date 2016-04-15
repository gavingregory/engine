#pragma once

#include "../system/SubSystem.h"
#include "../../../engine-physics/src/Physics.h"
#include "../input/InputHandler.h"
#include "../../../engine-common/src/system/CallbackFunctions.h"

class GameLogic : public SubSystem
{
public:
	GameLogic(Physics* physics, InputHandler* inputHandler);
	virtual ~GameLogic();
	virtual bool init() = 0;
	virtual bool destroy() = 0;
	virtual void update(float msec) = 0;
	void setInputEventCallback(InputEventCallback cb) {
		m_InputHandler->registerInputEventCallback(cb);
	}
	void setCollisionEventCallback(CollisionEventCallback cb) {
		m_Physics->registerCollisionEventCallback(cb);
	}
protected:
	Physics* m_Physics;
	InputHandler* m_InputHandler;
};

