#include "BatchRenderer2d.h"


namespace engine {
	namespace graphics {

		BatchRenderer2d::BatchRenderer2d() {
			init();
		}

		BatchRenderer2d::~BatchRenderer2d() {
			delete m_IBO;
			glDeleteBuffers(1, &m_VBO);
		}

		void BatchRenderer2d::init() {
			glGenVertexArrays(1, &m_VAO);
			glGenBuffers(1, &m_VBO);

			glBindVertexArray(m_VAO);
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
			glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);
			glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
			glEnableVertexAttribArray(SHADER_COLOUR_INDEX);
			glVertexAttribPointer(SHADER_VERTEX_INDEX, RENDERER_COMPONENTS_VEC3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)RENDERER_NO_OFFSET);
			glVertexAttribPointer(SHADER_COLOUR_INDEX, RENDERER_COMPONENTS_VEC4, GL_UNSIGNED_BYTE, GL_TRUE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::colour)));
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			GLuint* indices = new GLuint[RENDERER_INDICES_SIZE];
			
			int offset = 0;

			for (int i = 0; i < RENDERER_INDICES_SIZE; i+=6) {
				indices[i    ] = offset + 0;
				indices[i + 1] = offset + 1;
				indices[i + 2] = offset + 2;
				indices[i + 3] = offset + 2;
				indices[i + 4] = offset + 3;
				indices[i + 5] = offset + 0;

				offset += 4;
			}

			m_IBO = new IndexBuffer(indices, RENDERER_INDICES_SIZE);
			glBindVertexArray(0);

			// should this be here?
			delete[] indices;
		}

		void BatchRenderer2d::begin() {
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
			m_Buffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		}

		void BatchRenderer2d::submit(const Renderable2d* renderable) {

			const glm::vec3& position = renderable->getPosition();
			const glm::vec2& size = renderable->getSize();
			const glm::vec4& colour = renderable->getColour();

			int r = colour.r * 255.0f;
			int g = colour.g * 255.0f;
			int b = colour.b * 255.0f;
			int a = colour.a * 255.0f;

			unsigned int c = a << 24 | b << 16 | g << 8 | r;

			m_Buffer->vertex = position;
			m_Buffer->colour = c;
			m_Buffer++;

			m_Buffer->vertex = glm::vec3(position.x, position.y + size.y, position.z);
			m_Buffer->colour = c;
			m_Buffer++;

			m_Buffer->vertex = glm::vec3(position.x + size.x, position.y + size.y, position.z);
			m_Buffer->colour = c;
			m_Buffer++;

			m_Buffer->vertex = glm::vec3(position.x + size.x, position.y, position.z);;
			m_Buffer->colour = c;
			m_Buffer++;
			
			m_IndexCount += 6;
		}

		void BatchRenderer2d::end() {
			glUnmapBuffer(GL_ARRAY_BUFFER);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		void BatchRenderer2d::flush() {
			glBindVertexArray(m_VAO);
			m_IBO->bind();

			glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, NULL);

			m_IBO->unbind();
			glBindVertexArray(0);

			m_IndexCount = 0;
		}
	}
}
