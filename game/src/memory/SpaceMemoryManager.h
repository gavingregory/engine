#pragma once

#include "../../../engine-memory/src/MemoryManager.h"
#include "../entities/PlayerEntity.h"

class SpaceMemoryManager : public MemoryManager
{
public:
	SpaceMemoryManager();
	virtual ~SpaceMemoryManager();
	Entity* createPlayerEntity(PlayerEntityParams params);
};