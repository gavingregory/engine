#include "GameTimer.h"

namespace engine {
	namespace utils {

		GameTimer::GameTimer(void) {
			QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);
			QueryPerformanceCounter((LARGE_INTEGER *)&start);

			lastTime = GetMS();
		}

		/*
		Returns the Milliseconds since timer was started
		*/
		float GameTimer::GetMS() const {
			LARGE_INTEGER t;
			QueryPerformanceCounter(&t);
			return (float)((t.QuadPart - start.QuadPart) * 1000.0 / frequency.QuadPart);
		}

		float	 GameTimer::GetTimedMS() {
			float a = GetMS();
			float b = a - lastTime;
			lastTime = a;
			return b;
		}
	}
}