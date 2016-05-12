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
	
	// set spawn location to be at the start 
	m_SpawnState = SL_START;
	m_SpawnLocation = b2Vec2(0, 100);

	return 1;
}

bool GameLogic::destroy() {
	return 1;
}

void GameLogic::update(float msec) {

	// update the camera
	Camera* cam = Camera::Instance;
	map<string, Entity*>* entities = Level::LevelStack.top()->getEntities();
	Entity* player = entities->at("ship");
	vec3 pos = player->getPosition();
	Camera::vw_matrix = lookAt(vec3(pos.x, pos.y, pos.z + 3.0f), pos, vec3(0.0f, 1.0f, 0.0f));

	for (b2Contact* contact = Physics::CurrentWorld->GetContactList(); contact; contact = contact->GetNext()) {
		Entity* bodyDataA = (Entity*)contact->GetFixtureA()->GetBody()->GetUserData();
		Entity* bodyDataB = (Entity*)contact->GetFixtureB()->GetBody()->GetUserData();
		
		Entity* ship = nullptr;
		Entity* other = nullptr;

		if (bodyDataA->getName() == "ship") {
			ship = bodyDataA;
			other = bodyDataB;
		}
		else {
			ship = bodyDataB;
			other = bodyDataA;
		}

		// EXIT ENTITY
		if (other->getName() == "poo") {
			ISound* s = m_Audio->play("res/audio/Sfx11.wav", false);
			Window::quit = true;
		}
		// PLATFORM ENTITIES
		else if (other->getCategory() == EC_PLATFORM) {
			ISound* s = m_Audio->play("res/audio/Sfx1.wav", false);
			player->getPhysicsObject()->SetTransform(m_SpawnLocation, 90.f / 57.2958f);
			player->getPhysicsObject()->SetAngularVelocity(0.f);
			player->getPhysicsObject()->SetLinearVelocity(b2Vec2(0, 0));
			player->getPhysicsObject()->SetAwake(true);
		}
		// TRIGGER ENTITIES
		else if (other->getCategory() == EC_TRIGGER) {

			// SET ROOM WAYPOINT 01
			if (other->getName() == "set-waypoint-01") {
				if (m_SpawnState != SL_ROOM_01) {
					m_SpawnState = SL_ROOM_01;
					m_SpawnLocation = b2Vec2(675,500);
					ISound* s = m_Audio->play("res/audio/Sfx6.wav", false);
				}
			}

			// SET ROOM WAYPOINT 02
			else if (other->getName() == "set-waypoint-02") {
				if (m_SpawnState != SL_ROOM_02) {
					m_SpawnState = SL_ROOM_02;
					m_SpawnLocation = b2Vec2(-100, 500);
					ISound* s = m_Audio->play("res/audio/Sfx6.wav", false);
				}
			}

			// SET ROOM WAYPOINT 03
			else if (other->getName() == "set-waypoint-03") {
				if (m_SpawnState != SL_ROOM_03) {
					m_SpawnState = SL_ROOM_03;
					m_SpawnLocation = b2Vec2(-100, 1100);
					ISound* s = m_Audio->play("res/audio/Sfx6.wav", false);
				}
			}
		}
		// ENEMY ENTITIES
		else if (other->getCategory() == EC_ENEMY) {
			ISound* s = m_Audio->play("res/audio/Sfx10.wav", false);
			player->getPhysicsObject()->SetTransform(m_SpawnLocation, 90.f / 57.2958f);
			player->getPhysicsObject()->SetAngularVelocity(0.f);
			player->getPhysicsObject()->SetLinearVelocity(b2Vec2(0, 0));
			player->getPhysicsObject()->SetAwake(true);
		}
		else {
			cout << "Unknown COLLISION!" << endl;
		}

	}
}
