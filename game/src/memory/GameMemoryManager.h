/******************************************************************************
Class:GameMemoryManager
Author:Gavin Gregory
Description:As the memory manager cannot know about sub classes entity types,
the user must sub class memory manager and create entity factory functions for 
their own entity types. This was the downside to creating my own memory manager
that I could not find a way to overcome.
*//////////////////////////////////////////////////////////////////////////////

#pragma once

#include "../../../engine-memory/src/MemoryManager.h"
#include "../entities/PlayerEntity.h"
#include "../entities/EnemyEntity.h"
#include "../entities/TriggerEntity.h"

class GameMemoryManager : public MemoryManager
{
public:
	GameMemoryManager();
	virtual ~GameMemoryManager();
	Entity* createPlayerEntity(PlayerEntityParams params);
	Entity* createEnemyEntity(EnemyEntityParams params);
	Entity* createTriggerEntity(TriggerEntityParams params);
};