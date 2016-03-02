#include "CollisionCircle.h"

CollisionCircle::CollisionCircle(CollisionCircleParams params):
	CollisionShape(params.position), radius(params.radius) {}

CollisionCircle::~CollisionCircle() {}
