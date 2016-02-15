#pragma once

#include "Renderable2d.h"

namespace engine {
	namespace graphics {

		class Sprite : public Renderable2d
		{
		public:
			Sprite(float x, float y, float width, float height, const glm::vec4& colour);
			virtual ~Sprite();
		private:

		};

	}
}