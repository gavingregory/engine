#pragma once

#include "../../engine-common/src/graphics/Entity.h"
#include "../../engine-common/src/system/SubSystem.h"

#define GIGABYTE 1073741824

namespace engine {
	namespace system {
		using namespace graphics;

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

			Entity* createEntity();

			virtual bool init();
	
			virtual bool destroy();

			virtual void update(float msec);
		private:
			void*   m_BlockPointer;
			void*	m_MemoryPointer[OBJECT_END];
			int		m_Size[OBJECT_END];
			int		m_Count[OBJECT_END];
		};

	}
}
