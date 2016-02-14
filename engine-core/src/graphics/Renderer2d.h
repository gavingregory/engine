#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "Renderable2d.h"

namespace engine {
	namespace graphics {

		class Renderer2d
		{
		public:
			virtual void submit(const Renderable2d* renderable) =0;
			virtual void flush() =0;
		};

	}
}

