#include "CollisionCircle.h"

CollisionCircle::CollisionCircle(CollisionCircleParams params):
        Shape(params.position), radius(params.radius) {}

CollisionCircle::~CollisionCircle() {}
