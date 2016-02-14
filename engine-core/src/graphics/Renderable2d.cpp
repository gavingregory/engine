#include "Renderable2d.h"


namespace engine {
	namespace graphics {

		Renderable2d::Renderable2d(glm::vec3 position, glm::vec2 size, glm::vec4 colour, Shader& shader)
			: m_Position(position), m_Size(size), m_Colour(colour), m_Shader(shader)
		{
			m_VertexArray = new VertexArray();

			GLfloat vertices[] = {
				0,0,0,
				0,position.y, 0,
				position.x, position.y, 0,
				position.x, 0, 0
			};

			GLfloat colours[] = {
				colour.r, colour.g, colour.b, colour.a,
				colour.r, colour.g, colour.b, colour.a,
				colour.r, colour.g, colour.b, colour.a,
				colour.r, colour.g, colour.b, colour.a
			};

			m_VertexArray->addBuffer(new Buffer(vertices, 4 * 3, 3), 0);
			m_VertexArray->addBuffer(new Buffer(colours, 4 * 4, 4), 1);

			GLushort indices[] = { 0,1,2,2,3,0 };
			m_IndexBuffer = new IndexBuffer(indices, 6);
		}

		Renderable2d::~Renderable2d() {
			delete m_VertexArray;
			delete m_IndexBuffer;
		}

	}
}