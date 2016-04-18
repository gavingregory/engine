#include "BaseLogic.h"

BaseLogic::BaseLogic(Physics* physics, InputHandler* inputHandler) {
	m_Physics = physics;
	m_InputHandler = inputHandler;
}

BaseLogic::~BaseLogic() {}