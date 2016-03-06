#pragma once

#include "../../engine-common/src/graphics/Entity.h"
#include "../../engine-common/src/graphics/RenderObject.h"
#include "../../engine-common/src/system/SubSystem.h"
#include "../../engine-common/src/level/Level.h"

#define GIGABYTE 1073741824

enum ObjectType {
	OBJECT_ENTITY,
	OBJECT_PHYSICS,
	OBJECT_RENDER,
	OBJECT_END
};

class MemoryManager : public SubSystem
{
public:
	MemoryManager();
	virtual ~MemoryManager();

	Entity* createEntity(EntityParams params);
	RenderObject* createRenderObject(RenderObjectParams params);
	PhysicsObject* createPhysicsObject(PhysicsObjectParams params);
	Mesh* createMesh(string path);
	Shader* createShader(ShaderParams params);
	CollisionCircle* createCollisionCircle(CollisionCircleParams);
	CollisionPlane* createCollisionPlane(CollisionPlaneParams);
	Level* createLevel(LevelParams);
	virtual bool init();
	
	virtual bool destroy();

	virtual void update(float msec);
protected:
	vector<void*> m_Objects;
	//void*   m_BlockPointer;
	//void*	m_MemoryPointer[OBJECT_END];
	//int		m_Size[OBJECT_END];
	//int		m_Count[OBJECT_END];
};