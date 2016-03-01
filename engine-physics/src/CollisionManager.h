#pragma once

#include "collision\CollisionCircle.h"

class CollisionManager
{
public:
	CollisionManager();
	virtual ~CollisionManager();
	bool detect(CollisionCircle* left, CollisionCircle* right);
};