#include "GameMemoryManager.h"

GameMemoryManager::GameMemoryManager() : MemoryManager() {}

GameMemoryManager::~GameMemoryManager() {}

Entity* GameMemoryManager::createPlayerEntity(PlayerEntityParams params) {
	RenderObject* ro = createRenderObject(RenderObjectParams{ params.position, params.mesh, params.shader });
	PlayerEntity* e = new PlayerEntity(params, ro);
	m_Objects.push_back(e);
	return e;
}

Entity* GameMemoryManager::createEnemyEntity(EnemyEntityParams params) {
	RenderObject* ro = createRenderObject(RenderObjectParams{ params.position, params.mesh, params.shader });
	EnemyEntity* e = new EnemyEntity(params, ro);
	m_Objects.push_back(e);
	return e;
}