#pragma once

#include "Renderer2d.h"
#include "StaticSprite.h"
#include <glm/ext.hpp> // to_string(v)!
#include <deque>

namespace engine {
	namespace graphics {

		class SimpleRenderer2d : public Renderer2d
		{
		public:
			SimpleRenderer2d();
			virtual ~SimpleRenderer2d();
			void submit(const Renderable2d* renderable) override;
			void flush() override;
		private:
			std::deque<const StaticSprite*> m_RenderQueue;
		};

	}
}

