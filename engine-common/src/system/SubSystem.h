/******************************************************************************
Class:SubSystem
Author:Gavin Gregory
Description:SubSystem is the base class for each SubSystem in the game engine. This
forces each class to have init, destroy and update virtual methods. This way
each subsystem will get called every iteration of the game loop, and have the
ability to perform actions.
*//////////////////////////////////////////////////////////////////////////////

#pragma once

class SubSystem {
public:
	virtual bool init() = 0;
	virtual bool destroy() = 0;
	virtual void update(float msec) = 0;
};