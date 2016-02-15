#pragma once
#include "./buffers/Buffer.h"
#include "./buffers/IndexBuffer.h"
#include "./buffers/VertexArray.h"
#include "./Shader.h"
#include <glm/glm.hpp>

namespace engine {
	namespace graphics{

		struct VertexData {
			glm::vec3 vertex;
			glm::vec4 colour;
		};

		class Renderable2d
		{
		protected:

			glm::vec3 m_Position;
			glm::vec2 m_Size;
			glm::vec4 m_Colour;

		public:
			Renderable2d(glm::vec3 position, glm::vec2 size, glm::vec4 colour);
			virtual ~Renderable2d();

			inline const glm::vec3& getPosition() const { return m_Position; }
			inline const glm::vec2& getSize() const { return m_Size; }
			inline const glm::vec4& getColour() const { return m_Colour; }
		};

	}
}

