#include "CollisionRectangle.h"



CollisionRectangle::CollisionRectangle(CollisionRectangleParams params) :
	CollisionShape(params.position), m_Width(params.width), m_Height(params.height) {}

CollisionRectangle::~CollisionRectangle() {}