#include "MemoryManager.h"

MemoryManager::MemoryManager() {}

MemoryManager::~MemoryManager() {}

Entity* MemoryManager::createEntity(EntityParams params) {
	RenderObject* ro = createRenderObject(RenderObjectParams{ params.position, params.mesh, params.shader });
	PhysicsObject* po = createPhysicsObject(PhysicsObjectParams{ params.position, params.velocity, params.acceleration, ro, nullptr });
	Entity* e = new Entity(params, ro, po);
	m_Objects.push_back(e);
	return e;
}

RenderObject* MemoryManager::createRenderObject(RenderObjectParams params) {
	RenderObject* r = new RenderObject(params);
	m_Objects.push_back(r);
	return r;
}

PhysicsObject* MemoryManager::createPhysicsObject(PhysicsObjectParams params) {
	PhysicsObject* p = new PhysicsObject(params);
	m_Objects.push_back(p);
	return p;
}


Mesh* MemoryManager::createMesh(string path) {
	Mesh* m = Mesh::LoadMeshFile(path);
	m_Objects.push_back(m);
	return m;
}

Shader* MemoryManager::createShader(ShaderParams params) {
	Shader* s = new Shader(params);
	m_Objects.push_back(s);
	return s;
}

bool MemoryManager::init() {
	// allocate new memory
	//m_BlockPointer = malloc(GIGABYTE);
	//memset(m_BlockPointer, 0, GIGABYTE);
	return true;
}

bool MemoryManager::destroy() {
	//free (m_BlockPointer);
	//m_BlockPointer = nullptr;
	for (int i = 0; i < m_Objects.size(); i++) {
		delete m_Objects[i];
	}
	return true;
}

void MemoryManager::update(float msec) {
	// do nothing
}
