#pragma once

#include "../../../engine-memory/src/MemoryManager.h"
#include "../entities/NodeEntity.h"

class SpaceMemoryManager : public MemoryManager
{
public:
	SpaceMemoryManager();
	virtual ~SpaceMemoryManager();
	Entity* createNodeEntity(NodeEntityParams params);
};