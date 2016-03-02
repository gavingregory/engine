#include "CollisionPlane.h"

CollisionPlane::CollisionPlane(CollisionPlaneParams params) :
	CollisionShape(params.position), m_Normal(params.normal), m_Distance(params.distance) {}

CollisionPlane::~CollisionPlane() {}