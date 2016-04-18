#include "GameLogic.h"

int GameLogic::UniqueId = 0;

BaseLogic* GameLogic::GameLogicInstance;
InputTypes GameLogic::PlayerMovementState;

GameLogic::GameLogic(GameMemoryManager* memory, Physics* physics, InputHandler* inputHandler, Audio* audio)
	: BaseLogic(physics, inputHandler) {
	m_MemoryManager = memory;
	m_Audio = audio;

	GameLogic::GameLogicInstance = this;
		
	// initialise game states
	GameLogic::PlayerMovementState = IT_PLAYER_STOP;
}

GameLogic::~GameLogic() {}

bool GameLogic::init() {
	map<string, Mesh*>* meshes = Level::currentLevel->getMeshes();
	map<string, Shader*>* shaders = Level::currentLevel->getShaders();

	// set the level's logic controller
	Level::currentLevel->setLogic(this);

	Mesh* m = (*meshes)["asteroid"];
	Shader* s = (*shaders)["texture"];
	
	return 1;
}

bool GameLogic::destroy() {
	return 1;
}

void GameLogic::update(float msec) {
	for (b2Contact* contact = Physics::CurrentWorld->GetContactList(); contact; contact = contact->GetNext()) {
		Entity* bodyDataA = (Entity*)contact->GetFixtureA()->GetBody()->GetUserData();
		Entity* bodyDataB = (Entity*)contact->GetFixtureB()->GetBody()->GetUserData();
		if (bodyDataA->getName() == "ship" && bodyDataB->getName() == "poo") {
			// WIN!
			ISound* s = m_Audio->play("res/audio/fart-2.wav", false);
			Window::quit = true;
		}
	}
}
