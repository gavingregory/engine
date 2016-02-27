#pragma once

#include "collision\Circle.h"

class Collision
{
public:
	static bool Detect(Circle* left, Circle* right);
};

