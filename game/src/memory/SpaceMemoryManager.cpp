#include "SpaceMemoryManager.h"

SpaceMemoryManager::SpaceMemoryManager() : MemoryManager() {}

SpaceMemoryManager::~SpaceMemoryManager() {}

Entity* SpaceMemoryManager::createNodeEntity(NodeEntityParams params) {
	RenderObject* ro = createRenderObject(RenderObjectParams{ params.position, params.mesh, params.shader });
	NodeEntity* e = new NodeEntity(params, ro);
	m_Objects.push_back(e);
	return e;
}
