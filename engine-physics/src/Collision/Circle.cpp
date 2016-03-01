#include "Circle.h"

Circle::Circle(glm::vec3* position, float radius):
        Shape(position), radius(radius) {}

Circle::~Circle() {}
