#pragma once

#include "collision\Circle.h"

class CollisionManager
{
public:
	CollisionManager();
	virtual ~CollisionManager();
	bool detect(Circle* left, Circle* right);
};

