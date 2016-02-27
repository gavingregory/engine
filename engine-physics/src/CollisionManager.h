#pragma once

#include "collision\Circle.h"

class CollisionManager
{
public:
	static bool Detect(Circle* left, Circle* right);
};

