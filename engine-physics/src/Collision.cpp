#include "Collision.h"


bool Collision::Detect(Circle* left, Circle* right) {
	if (left == nullptr || right == nullptr) return false;
	float distance = glm::distance(*left->getPositionPtr(), *right->getPositionPtr());
	if (distance < left->get_radius() || distance < right->get_radius())
		return true;
	return false;
}