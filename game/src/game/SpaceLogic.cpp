#include "SpaceLogic.h"

SpaceLogic::SpaceLogic() {}

SpaceLogic::~SpaceLogic() {}

bool SpaceLogic::init() {
	return 1;
}

bool SpaceLogic::destroy() {
	return 1;
}

void SpaceLogic::update(float msec) {
	m_PlayerState.update(msec);
}