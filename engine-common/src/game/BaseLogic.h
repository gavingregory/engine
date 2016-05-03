/******************************************************************************
Class:GameLogic
Author:Gavin Gregory
Description:Base class for game logic. This should be sub classed by
the user in their game project
*//////////////////////////////////////////////////////////////////////////////

#pragma once

#include "../system/SubSystem.h"
#include "../../../engine-physics/src/Physics.h"
#include "../input/InputHandler.h"

class BaseLogic : public SubSystem
{
public:
	BaseLogic(Physics* physics, InputHandler* inputHandler);
	virtual ~BaseLogic();
	virtual bool init() = 0;
	virtual bool destroy() = 0;
	virtual void update(float msec) = 0;
protected:
	Physics* m_Physics;
	InputHandler* m_InputHandler;
};

