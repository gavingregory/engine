#include "SnookerMemoryManager.h"

SnookerMemoryManager::SnookerMemoryManager() : MemoryManager() {}

SnookerMemoryManager::~SnookerMemoryManager() {}

Entity* SnookerMemoryManager::createBallEntity(BallEntityParams params) {
	RenderObject* ro = createRenderObject(RenderObjectParams{ params.position, params.mesh, params.shader });
	PhysicsObject* po = createPhysicsObject(PhysicsObjectParams{ params.position, params.velocity, params.acceleration, ro, nullptr });
	CollisionCircle* c = createCollisionCircle(CollisionCircleParams{ po->getPositionPtr() , params.radius });
	BallEntity* e = new BallEntity(params, ro, po, c);
	m_Objects.push_back(e);
	return e;
}

Entity* SnookerMemoryManager::createCushionEntity(CushionEntityParams params) {
	RenderObject* ro = createRenderObject(RenderObjectParams{ params.position, params.mesh, params.shader });
	PhysicsObject* po = createPhysicsObject(PhysicsObjectParams{ params.position, params.velocity, params.acceleration, ro, nullptr });
	CollisionRectangle* r = createCollisionRectangle(CollisionRectangleParams{ po->getPositionPtr() , params.width, params.height });
	CushionEntity* e = new CushionEntity(params, ro, po, r);
	m_Objects.push_back(e);
	return e;
}