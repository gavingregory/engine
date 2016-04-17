#include "SpaceLogic.h"

int SpaceLogic::UniqueId = 0;

SpaceLogic* SpaceLogic::GameLogicInstance;
InputTypes SpaceLogic::PlayerMovementState;

SpaceLogic::SpaceLogic(SpaceMemoryManager* memory, Physics* physics, InputHandler* inputHandler)
	: GameLogic(physics, inputHandler) {
	m_MemoryManager = memory;

	SpaceLogic::GameLogicInstance = this;
		
	// initialise game states
	SpaceLogic::PlayerMovementState = IT_PLAYER_STOP;
}

SpaceLogic::~SpaceLogic() {}

bool SpaceLogic::init() {
	map<string, Mesh*>* meshes = Level::currentLevel->getMeshes();
	map<string, Shader*>* shaders = Level::currentLevel->getShaders();

	// set the level's logic controller
	Level::currentLevel->setLogic(this);

	Mesh* m = (*meshes)["asteroid"];
	Shader* s = (*shaders)["texture"];
	
	return 1;
}

bool SpaceLogic::destroy() {
	return 1;
}

void SpaceLogic::update(float msec) {
	//
}
