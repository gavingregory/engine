#pragma once
#include "buffers/VertexArray.h"
#include "buffers/IndexBuffer.h"
#include "Renderable2d.h"
#include "Shader.h"
#define PI 3.141592653589793238463

namespace engine {
	namespace graphics {

		class Circle : public Renderable2d
		{
		public:
			Circle(const float x, const float y, const float r, const int points, const glm::vec4 colour, Shader& shader);
			virtual ~Circle();

			inline const VertexArray* getVAO() const { return m_VertexArray; }
			inline const IndexBuffer* getIBO() const { return m_IndexBuffer; }
			inline Shader& getShader() const { return m_Shader; }

		private:
			VertexArray* m_VertexArray;
			IndexBuffer* m_IndexBuffer;
			Shader& m_Shader;

			static glm::vec3 rotateVector(glm::vec3 v, float degrees) {
				double rad = degrees * (PI / 180);
				double ca = cos(rad);
				double sa = sin(rad);
				return glm::vec3(
					(v.x*ca) - (v.y*sa),
					(v.x*sa) + (v.y*ca),
					0);
			}
		};

	}
}