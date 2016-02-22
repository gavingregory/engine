#pragma once
#include <glm/glm.hpp>
#include "Entity.h"

namespace engine {
	namespace graphics {

		class Camera : Entity
		{
		public:
			Camera(glm::mat4 viewMatrix);
			virtual ~Camera();
			void setViewMatrix(const glm::mat4 viewMatrix) { m_ViewMatrix = viewMatrix; }
			glm::mat4 getViewMatrix() const { return m_ViewMatrix; }

			virtual void update(float dt) override;
			virtual void render(Renderer* renderer) override;
		private:
			glm::mat4 m_ViewMatrix;
		};

	}
}

