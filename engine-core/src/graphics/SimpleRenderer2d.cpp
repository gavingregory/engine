#include "SimpleRenderer2d.h"


namespace engine {
	namespace graphics {

		SimpleRenderer2d::SimpleRenderer2d() {}

		SimpleRenderer2d::~SimpleRenderer2d() {}

		void SimpleRenderer2d::submit(const Renderable2d* renderable) {
			m_RenderQueue.push_back(renderable);
		}
		
		void SimpleRenderer2d::flush() {
			while (!m_RenderQueue.empty())
			{
				const Renderable2d* renderable = m_RenderQueue.front();
				renderable->getVAO()->bind();
				renderable->getIBO()->bind();

				renderable->getShader().setUniformMat4("ml_matrix", glm::translate(renderable->getPosition()));
				glDrawElements(GL_TRIANGLES, renderable->getIBO()->getCount(), GL_UNSIGNED_SHORT, nullptr);

				renderable->getIBO()->unbind();
				renderable->getVAO()->unbind();

				m_RenderQueue.pop_front();
			}
		}

	}
}