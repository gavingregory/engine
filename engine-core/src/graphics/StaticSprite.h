#pragma once
#include "buffers/VertexArray.h"
#include "buffers/IndexBuffer.h"
#include "Renderable2d.h"
#include "Shader.h"

namespace engine {
	namespace graphics {

		class StaticSprite : public Renderable2d
		{
		public:
			StaticSprite(float x, float y, float width, float height, const glm::vec4 colour, Shader& shader);
			virtual ~StaticSprite();

			inline const VertexArray* getVAO() const { return m_VertexArray; }
			inline const IndexBuffer* getIBO() const { return m_IndexBuffer; }
			inline Shader& getShader() const { return m_Shader; }

		private:
			VertexArray* m_VertexArray;
			IndexBuffer* m_IndexBuffer;
			Shader& m_Shader;
		};

	}
}