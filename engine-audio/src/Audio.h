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
			virtual bool init();
			virtual bool destroy();
			virtual void update(float msec);
			void play();
			void stop();
		private:
			PaStream *m_Stream;
		};
	}
}
