#include "GameLogic.h"

GameLogic::GameLogic(Physics* physics, InputHandler* inputHandler) {
	m_Physics = physics;
	m_InputHandler = inputHandler;
}

GameLogic::~GameLogic() {}