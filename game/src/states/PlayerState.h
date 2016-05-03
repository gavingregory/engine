#pragma once

enum PlayerStates {
	PS_MOVE_LEFT,
	PS_MOVE_RIGHT,
	PS_STATIONARY
};

class PlayerState {
public:
	void update(float msec) {
		switch (m_State) {
		case PS_MOVE_LEFT:
			break;
		case PS_MOVE_RIGHT:
			break;
		case PS_STATIONARY:
			break;
		}
	}
	PlayerStates m_State;
};