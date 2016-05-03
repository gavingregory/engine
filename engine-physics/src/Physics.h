/******************************************************************************
Class:Physics
Author:Gavin Gregory
Description:The physics subsystem handles physics related functions.
*//////////////////////////////////////////////////////////////////////////////

#pragma once

#include "../../engine-common/src/system/SubSystem.h"
#include <Box2D\Box2D.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <iostream>

using glm::vec3;

class Physics : public SubSystem
{
public:
	Physics(float gravity);
	virtual ~Physics();
	bool init();
	bool destroy();
	void update(float msec);
	static b2World* CurrentWorld;
private:
	float m_Gravity;
	b2World m_World;
};
