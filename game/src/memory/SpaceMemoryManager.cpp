#include "SpaceMemoryManager.h"

SpaceMemoryManager::SpaceMemoryManager() : MemoryManager() {}

SpaceMemoryManager::~SpaceMemoryManager() {}

Entity* SpaceMemoryManager::createNodeEntity(NodeEntityParams params) {
	RenderObject* ro = createRenderObject(RenderObjectParams{ params.position, params.mesh, params.shader });
	PhysicsObject* po = createPhysicsObject(PhysicsObjectParams{ params.position, params.velocity, params.acceleration, params.rotation, params.mass, ro, nullptr });
	CollisionCircle* c = createCollisionCircle(CollisionCircleParams{ po->getPositionPtr() , params.radius });
	NodeEntity* e = new NodeEntity(params, ro, po, c);
	m_Objects.push_back(e);
	return e;
}

Entity* SpaceMemoryManager::createCushionEntity(CushionEntityParams params) {
	RenderObject* ro = createRenderObject(RenderObjectParams{ params.position, params.mesh, params.shader });
	PhysicsObject* po = createPhysicsObject(PhysicsObjectParams{ params.position, params.velocity, params.acceleration, params.rotation, params.mass, ro, nullptr });
	CollisionPlane* r = createCollisionPlane(CollisionPlaneParams{ po->getPositionPtr() , params.normal, params.distance });
	CushionEntity* e = new CushionEntity(params, ro, po, r);
	m_Objects.push_back(e);
	return e;
}