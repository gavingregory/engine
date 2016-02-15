#include "Sprite.h"



namespace engine {
	namespace graphics {

		Sprite::Sprite(float x, float y, float width, float height, const glm::vec4& colour)
			: Renderable2d(glm::vec3(x, y, 0), glm::vec2(width, height), colour) { }

		Sprite::~Sprite() { }

	}
}