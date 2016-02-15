#include "SimpleRenderer2d.h"


namespace engine {
	namespace graphics {

		SimpleRenderer2d::SimpleRenderer2d() {}

		SimpleRenderer2d::~SimpleRenderer2d() {}

		void SimpleRenderer2d::submit(const Renderable2d* renderable) {
			m_RenderQueue.push_back((StaticSprite*)renderable);
		}
		
		void SimpleRenderer2d::flush() {
			while (!m_RenderQueue.empty())
			{
				const StaticSprite* sprite = m_RenderQueue.front();
				sprite->getVAO()->bind();
				sprite->getIBO()->bind();

				sprite->getShader().setUniformMat4("ml_matrix", glm::translate(sprite->getPosition()));
				glDrawElements(GL_TRIANGLES, sprite->getIBO()->getCount(), GL_UNSIGNED_SHORT, nullptr);

				sprite->getIBO()->unbind();
				sprite->getVAO()->unbind();

				m_RenderQueue.pop_front();
			}
		}

	}
}