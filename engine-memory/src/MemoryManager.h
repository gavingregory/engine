#pragma once

#include "../../engine-core/src/graphics/Entity.h"
#include "../../engine-common/src/system/SubSystem.h"

namespace engine {
	namespace system {
		using namespace graphics;

		enum ObjectType {
			OBJECT_ENTITY,
			OBJECT_PHYSICS,
			OBJECT_RENDER
		};

		class MemoryManager : public SubSystem
		{
		public:
			MemoryManager();
			virtual ~MemoryManager();

			Entity* createEntity();

			virtual bool init() {};
	
			virtual bool destroy() {};

			virtual void update(float msec) {};

		};

	}
}
