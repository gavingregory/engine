#include "SpaceLogic.h"

SpaceLogic::SpaceLogic() {
	m_GameState = SELECT_MODE;
	m_BuildState = BASIC_NODE;
}

SpaceLogic::~SpaceLogic() {}

bool SpaceLogic::init() {
	return 1;
}

bool SpaceLogic::destroy() {
	return 1;
}

void SpaceLogic::update(float msec) {

	switch (m_GameState) {
	case BUILD_MODE:
		switch (m_BuildState) {
		case BASIC_NODE:
			cout << "building basic node" << endl;
			break;
		case HARVESTER_NODE:
			cout << "building harvester node" << endl;
			break;
		case ENERGY_NODE:
			cout << "building energy node" << endl;
			break;
		case STORAGE_NODE:
			cout << "building storage node" << endl;
			break;
		case LASER_NODE:
			cout << "building laser node" << endl;
			break;
		}
		break;
	case SELECT_MODE:
		cout << "select mode" << endl;
	}
}