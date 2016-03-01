//
// Created by gavin on 24/10/15.
//

#ifndef COLLISION_CIRCLE_H
#define COLLISION_CIRCLE_H

#include <math.h>
#include "Shape.h"

//
// Circle Class, extends Shape
// Represents a circle object. Circles have a radius. The x and y position of a circle is in the centre!
//

class SingleVisitor;

class Circle : public Shape {
public:
    Circle(glm::vec3* position, float radius);
    ~Circle();
	inline float get_radius() const { return radius; }

private:
    float radius;
};


#endif //COLLISION_CIRCLE_H
