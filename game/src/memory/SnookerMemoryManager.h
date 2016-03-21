#pragma once

#include "../../../engine-memory/src/MemoryManager.h"
#include "../entities/BallEntity.h"
#include "../entities/CushionEntity.h"
#include "../entities/PocketEntity.h"

class SnookerMemoryManager : public MemoryManager
{
public:
	SnookerMemoryManager();
	virtual ~SnookerMemoryManager();
	Entity* createBallEntity(BallEntityParams params);
	Entity* createCushionEntity(CushionEntityParams params);
	Entity* createPocketEntity(PocketEntityParams params);
};