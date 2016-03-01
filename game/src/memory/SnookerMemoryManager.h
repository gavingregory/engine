#pragma once

#include "../../../engine-memory/src/MemoryManager.h"
#include "../entities/BallEntity.h"

class SnookerMemoryManager : public MemoryManager
{
public:
	SnookerMemoryManager();
	virtual ~SnookerMemoryManager();
	Entity* createBallEntity(BallEntityParams params);
};