#include "Renderable2d.h"


namespace engine {
	namespace graphics {

		Renderable2d::Renderable2d(glm::vec3 position, glm::vec2 size, glm::vec4 colour)
			: m_Position(position), m_Size(size), m_Colour(colour) { }

		Renderable2d::~Renderable2d() { }

	}
}