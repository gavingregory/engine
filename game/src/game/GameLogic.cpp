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
	map<string, Mesh*>* meshes = Level::LevelStack.top()->getMeshes();
	map<string, Shader*>* shaders = Level::LevelStack.top()->getShaders();

	// set the level's logic controller
	Level::LevelStack.top()->setLogic(this);

	Mesh* m = (*meshes)["asteroid"];
	Shader* s = (*shaders)["texture"];
	
	return 1;
}

bool GameLogic::destroy() {
	return 1;
}

void GameLogic::update(float msec) {

	// update the camera?
	Camera* cam = Camera::Instance;
	map<string, Entity*>* entities = Level::LevelStack.top()->getEntities();
	Entity* player = entities->at("ship");
	vec3 pos = player->getPosition();
	Camera::vw_matrix = lookAt(vec3(pos.x, pos.y, pos.z + 3.0f), pos, vec3(0.0f, 1.0f, 0.0f));

	for (b2Contact* contact = Physics::CurrentWorld->GetContactList(); contact; contact = contact->GetNext()) {
		Entity* bodyDataA = (Entity*)contact->GetFixtureA()->GetBody()->GetUserData();
		Entity* bodyDataB = (Entity*)contact->GetFixtureB()->GetBody()->GetUserData();
		
		// Win collision
		if (bodyDataA->getName() == "ship" && bodyDataB->getName() == "poo") {
			// WIN!
			ISound* s = m_Audio->play("res/audio/fart-2.wav", false);
			Window::quit = true;
		} else if (bodyDataA->getName() == "ship" || bodyDataB->getName() == "ship") {
			if (bodyDataA->getCategory() == EC_PLATFORM || bodyDataB->getCategory() == EC_PLATFORM) {

				player->getPhysicsObject()->SetTransform(b2Vec2(0, 100), 90.f / 57.2958f);
				cout << "platofmr collision" << endl;
				player->getPhysicsObject()->SetAngularVelocity(0.f);
				player->getPhysicsObject()->SetLinearVelocity(b2Vec2(0, 0));
				player->getPhysicsObject()->SetAwake(true);

			}

		}
		else {
			cout << bodyDataA->getName() << " " << bodyDataB->getName() << endl;
		}

	}
}
