#include "SpaceLogic.h"

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
		m_BuildEntity->getPhysicsObject()->setPosition(vec3(m_MousePosition, 0));
		switch (m_BuildState) {
		case BASIC_NODE:
			cout << "building basic node" << endl;
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
	Entity* e = m_MemoryManager->createNodeEntity(NodeEntityParams{
		vec3(m_MousePosition, 0), vec3(0), vec3(0), 0.0f, 1.0f,
		(*Level::currentLevel->getMeshes())["asteroid"],
		(*Level::currentLevel->getShaders())["texture"],
		"NodeEntity",
		1.0f
	});
	(*Level::currentLevel->getEntities()).insert(pair<string, Entity*>(e->getName(), e));
}