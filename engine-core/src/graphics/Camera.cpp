#include "Camera.h"


namespace engine {
	namespace graphics {

		Camera::Camera(glm::mat4 viewMatrix)
			: m_ViewMatrix(viewMatrix) {}

		Camera::~Camera() {}


		void Camera::update(float dt) {
			Entity::update(dt);
		}

		void Camera::render(Renderer* renderer) {
			renderer->Render(this->renderObject);
		}

	}
}