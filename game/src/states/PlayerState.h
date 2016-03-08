#pragma once

#include "../../../engine-common/src/game/State.h"

enum PlayerStates {
	Building,
	NotBuilding
};

class PlayerState : public State {
public:
	void update(float msec) {
		switch (m_State) {
		case Building:
			break;
		case NotBuilding:
			break;
		}
	}
	PlayerStates m_State;
};