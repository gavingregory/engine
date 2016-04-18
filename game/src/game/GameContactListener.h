#pragma once
#include <Box2D/Dynamics/b2WorldCallbacks.h>

class GameContactListener : public b2ContactListener
{
public:
	GameContactListener();
	~GameContactListener();
	virtual void BeginContact(b2Contact* contact) override {
		
	}

	virtual void EndContact(b2Contact* contact) override {

	}
};