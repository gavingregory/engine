#include "MemoryManager.h"


namespace engine {
	namespace system {

		MemoryManager::MemoryManager() {}

		MemoryManager::~MemoryManager() {}

		Entity* MemoryManager::createEntity() {
			if (m_BlockPointer) free(m_BlockPointer);
			m_BlockPointer = nullptr;
			return nullptr;
		}

		bool MemoryManager::init() {
			// allocate new memory
			m_BlockPointer = malloc(GIGABYTE);
			memset(m_BlockPointer, 0, GIGABYTE);
			return true;
		}

		bool MemoryManager::destroy() {
			free (m_BlockPointer);
			m_BlockPointer = nullptr;
			return true;
		}

		void MemoryManager::update(float msec) {
			
		}

	}
}