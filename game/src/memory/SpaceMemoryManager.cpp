#include "SpaceMemoryManager.h"

SpaceMemoryManager::SpaceMemoryManager() : MemoryManager() {}

SpaceMemoryManager::~SpaceMemoryManager() {}

Entity* SpaceMemoryManager::createPlayerEntity(PlayerEntityParams params) {
	RenderObject* ro = createRenderObject(RenderObjectParams{ params.position, params.mesh, params.shader });
	PlayerEntity* e = new PlayerEntity(params, ro);
	m_Objects.push_back(e);
	return e;
}