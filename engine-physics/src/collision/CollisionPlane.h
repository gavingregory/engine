#pragma once
#include "C:\Users\gavin\Dropbox\Projects\cpp\engine\engine-physics\src\collision\CollisionShape.h"

#include <glm/glm.hpp>

using glm::vec3;

struct CollisionPlaneParams {
	vec3* position;
	vec3 normal;
	vec3 distance;
};

class CollisionPlane :
	public CollisionShape
{
public:
	CollisionPlane(CollisionPlaneParams params);
	virtual ~CollisionPlane();
	vec3 getNormal() const { return m_Normal; }
	vec3 getDistance() const { return m_Distance; }
private:
	vec3 m_Normal;
	vec3 m_Distance;
};

