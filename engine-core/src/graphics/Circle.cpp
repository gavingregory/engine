#include "Circle.h"


namespace engine {
	namespace graphics {

		Circle::Circle(const float x, const float y, const float r, const int points, const glm::vec4 colour, Shader& shader)
			: Renderable2d(glm::vec3(x,y,0), glm::vec2(r*2, r*2), colour), m_Shader(shader) {
			
			m_VertexArray = new VertexArray();

			GLfloat vertices[33];
			GLfloat colours[44];
			float angle = 11.0f / 360.0f;
			glm::vec3 workingVector(0, r, 0);
			vertices[0] = 0.0f;
			vertices[1] = 0.0f;
			vertices[2] = 0.0f;
			

			for (int i = 3; i < 33; i+=3) {
				vertices[i] = workingVector.x;
				vertices[i + 1] = workingVector.y;
				vertices[i + 2] = workingVector.z;
				rotateVector(workingVector, angle);
			}

			for (int i = 0; i < 44; i += 4) {
				colours[i] = colour.r;
				colours[i+1] = colour.g;
				colours[i+2] = colour.b;
				colours[i+3] = colour.a;
			}

			m_VertexArray->addBuffer(new Buffer(vertices, 11 * 3, 3), 0);
			m_VertexArray->addBuffer(new Buffer(colours, 11 * 4, 4), 1);

			GLushort indices[30];
			int index = 0;
			for (int i = 0; i < 30; i += 3) {
				indices[i] = 0;
				indices[i + 1] = ;
			}


			m_IndexBuffer = new IndexBuffer(indices, 6);
		}


		Circle::~Circle()
		{
			delete m_VertexArray;
			delete m_IndexBuffer;
		}
	}
}