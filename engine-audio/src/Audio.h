#pragma once
#include "../../lib/portaudio/include/portaudio.h"
#include "../../engine-common/src/system/SubSystem.h"
#include <iostream>

using namespace engine;
using namespace system;

namespace engine {
	namespace audio {
		class Audio : public SubSystem
		{
		public:
			Audio();
			~Audio();
			virtual bool init() { return 0; }
			virtual bool destroy() { return 0; }
			virtual bool update(float msec) { return 0; }
		};
	}
}
