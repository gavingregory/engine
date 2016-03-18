#include "SpaceLogic.h"

int SpaceLogic::UniqueId = 0;

SpaceLogic::SpaceLogic(SpaceMemoryManager* memory) {
	m_MemoryManager = memory;

	m_GameState = GS_SELECT;
	m_BuildState = BASIC_NODE;
}

SpaceLogic::~SpaceLogic() {}

bool SpaceLogic::init() {
	map<string, Mesh*>* meshes = Level::currentLevel->getMeshes();
	map<string, Shader*>* shaders = Level::currentLevel->getShaders();

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
	switch (m_GameState) {
	case GS_BUILD:
		(*Level::currentLevel->getEntities()).insert_or_assign("buildingItem", m_BuildEntity);
		m_BuildEntity->getPhysicsObject()->SetTransform(b2Vec2(m_MousePosition.x, m_MousePosition.y), m_BuildEntity->getPhysicsObject()->GetAngle());
		switch (m_BuildState) {
		case BASIC_NODE:
			m_BuildEntity->getRenderObject()->getTextures()->insert_or_assign("tex", (*Level::currentLevel->getTextures())["node"]);
			break;
		case HARVESTER_NODE:
			m_BuildEntity->getRenderObject()->getTextures()->insert_or_assign("tex", (*Level::currentLevel->getTextures())["energy"]);
			
			cout << "building harvester node" << endl;
			break;
		case ENERGY_NODE:
			cout << "building energy node" << endl;
			break;
		case STORAGE_NODE:
			cout << "building storage node" << endl;
			break;
		case LASER_NODE:
			cout << "building laser node" << endl;
			break;
		}
		break;
	case GS_SELECT:
		(*Level::currentLevel->getEntities()).erase("buildingItem");
		cout << "select mode" << endl;
		break;
	case GS_PLACING:
		switch (m_BuildState) {
		case BASIC_NODE:
			buildBasicNode();
			break;
		case HARVESTER_NODE:
			cout << "building harvester node" << endl;
			break;
		case ENERGY_NODE:
			cout << "building energy node" << endl;
			break;
		case STORAGE_NODE:
			cout << "building storage node" << endl;
			break;
		case LASER_NODE:
			cout << "building laser node" << endl;
			break;
		}
		m_GameState = GS_SELECT; // reset game state
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