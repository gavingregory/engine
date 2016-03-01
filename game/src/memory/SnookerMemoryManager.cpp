#include "SnookerMemoryManager.h"

SnookerMemoryManager::SnookerMemoryManager() : MemoryManager() {}

SnookerMemoryManager::~SnookerMemoryManager() {}

Entity* SnookerMemoryManager::createBallEntity(BallEntityParams params) {
	BallEntity* b = new BallEntity(params);
	m_Objects.push_back(b);
	return b;
}