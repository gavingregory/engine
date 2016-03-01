#pragma once

#include <math.h>
#include "Shape.h"

//
// Circle Class, extends Shape
// Represents a circle object. Circles have a radius. The x and y position of a circle is in the centre!
//

using glm::vec3;

struct CollisionCircleParams {
	vec3* position;
	float radius;
};

class CollisionCircle : public Shape {
public:
	CollisionCircle(CollisionCircleParams params);
    ~CollisionCircle();
	inline float get_radius() const { return radius; }

private:
    float radius;
};
