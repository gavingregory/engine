#pragma once
#include "C:\Users\gavin\Dropbox\Projects\cpp\engine\engine-physics\src\collision\CollisionShape.h"

#include <glm/glm.hpp>

using glm::vec3;

struct CollisionRectangleParams {
	vec3* position;
	float width;
	float height;
};

class CollisionRectangle :
	public CollisionShape
{
public:
	CollisionRectangle(CollisionRectangleParams params);
	virtual ~CollisionRectangle();
	float getWidth() const { return m_Width; }
	float getHeight() const { return m_Height; }
private:
	float m_Width;
	float m_Height;
};

