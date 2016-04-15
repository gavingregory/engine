#include "SpaceLogic.h"

int SpaceLogic::UniqueId = 0;

SpaceLogic* SpaceLogic::GameLogicInstance;
InputTypes SpaceLogic::PlayerMovementState;

void CollisionCallback(pair<void*, void*> entities) {
	// do nothing at the moment
	cout << "something" << endl;
}

void InputCallback(bool isKeyboard, bool isPressed, int id) {
	// modify the player movement state
	if (isKeyboard && id == GLFW_KEY_W) {
		if (isPressed) SpaceLogic::PlayerMovementState = IT_PLAYER_UP;
		else SpaceLogic::PlayerMovementState = IT_PLAYER_STOP;
	} else if (isKeyboard && id == GLFW_KEY_S) {
		if (isPressed) SpaceLogic::PlayerMovementState = IT_PLAYER_DOWN;
		else SpaceLogic::PlayerMovementState = IT_PLAYER_STOP;
	} else if (isKeyboard && id == GLFW_KEY_A) {
		if (isPressed) SpaceLogic::PlayerMovementState = IT_PLAYER_LEFT;
		else SpaceLogic::PlayerMovementState = IT_PLAYER_STOP;
	} else if (isKeyboard && id == GLFW_KEY_D) {
		if (isPressed) SpaceLogic::PlayerMovementState = IT_PLAYER_RIGHT;
		else SpaceLogic::PlayerMovementState = IT_PLAYER_STOP;
	}
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

	map<string, Entity*>* entities = Level::currentLevel->getEntities();
	Entity* ship = entities->at("ship");

	float magnitude = 0.1f;
	b2Vec2 force = b2Vec2(cos(ship->getPhysicsObject()->GetAngle()) * magnitude, sin(ship->getPhysicsObject()->GetAngle()) * magnitude);
	
	switch (SpaceLogic::PlayerMovementState) {
	case IT_PLAYER_STOP:
		break;
	case IT_PLAYER_UP:
		ship->getPhysicsObject()->ApplyForce(force, ship->getPhysicsObject()->GetPosition(), true);
		break;
	case IT_PLAYER_DOWN:
		break;
	case IT_PLAYER_LEFT:
		ship->getPhysicsObject()->SetAngularDamping(0.001f);
		ship->getPhysicsObject()->SetAngularVelocity(0.001f);
		break;
	case IT_PLAYER_RIGHT:
		ship->getPhysicsObject()->SetAngularDamping(0.001f);
		ship->getPhysicsObject()->SetAngularVelocity(-0.001f);
		break;
	}
}

void SpaceLogic::buildBasicNode() {
	// create a new unique name (and increment the unique id counter)
	string name = "NodeEntity" + to_string(UniqueId++);

	// create the new entity through the memory manager
	Entity* e = m_MemoryManager->createNodeEntity(NodeEntityParams{
		vec3(m_MousePosition, 0), vec3(0), vec3(0), 0.0f, 1.0f,
		(*Level::currentLevel->getMeshes())["asteroid"],
		(*Level::currentLevel->getShaders())["texture"],
		name,
		1.0f
	});

	// insert into the level entities
	(*Level::currentLevel->getEntities()).insert(pair<string, Entity*>(name, e));
}