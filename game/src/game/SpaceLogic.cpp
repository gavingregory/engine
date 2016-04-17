#include "SpaceLogic.h"

int SpaceLogic::UniqueId = 0;

SpaceLogic* SpaceLogic::GameLogicInstance;
InputTypes SpaceLogic::PlayerMovementState;

void CollisionCallback(pair<void*, void*> entities) {
	// do nothing at the moment
	cout << "something" << endl;
}

void InputCallback(bool isKeyboard, bool isPressed, int id) {
	// do nothing at the moment
}

SpaceLogic::SpaceLogic(SpaceMemoryManager* memory, Physics* physics, InputHandler* inputHandler)
	: GameLogic(physics, inputHandler) {
	m_MemoryManager = memory;

	SpaceLogic::GameLogicInstance = this;

	// set the callback functions
	setCollisionEventCallback(&CollisionCallback);
	setInputEventCallback(&InputCallback);
	
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
	m_BuildEntity = m_MemoryManager->createEntity(EntityParams{ vec3(m_MousePosition, 0.0f), vec3(), vec3(), 0.0f, 1.0f, m, s, "buildingItem" });

	Level::currentLevel->getEntities()->insert(pair<string, Entity*>("buildingItem", m_BuildEntity));
	
	return 1;
}

bool SpaceLogic::destroy() {
	return 1;
}

void SpaceLogic::update(float msec) {
	//
}
