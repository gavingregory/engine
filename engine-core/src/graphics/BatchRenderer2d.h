#pragma once

#include "Renderer2d.h"
#include "buffers/IndexBuffer.h"


namespace engine {
	namespace graphics {

#define RENDERER_MAX_SPRITES  10000
#define RENDERER_VERTEX_SIZE  sizeof(VertexData)
#define RENDERER_SPRITE_SIZE  RENDERER_VERTEX_SIZE * 4
#define RENDERER_BUFFER_SIZE  RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
#define RENDERER_INDICES_SIZE RENDERER_MAX_SPRITES * 6

#define SHADER_VERTEX_INDEX 0
#define SHADER_COLOUR_INDEX 1

#define RENDERER_NO_OFFSET 0

#define RENDERER_COMPONENTS_VEC2 2
#define RENDERER_COMPONENTS_VEC3 3
#define RENDERER_COMPONENTS_VEC4 4

		class BatchRenderer2d : public Renderer2d
		{
		public:
			void submit(const Renderable2d* renderable) override;
			void flush() override;

			void begin();
			void end();

			BatchRenderer2d();
			~BatchRenderer2d();
		private:
			GLuint m_VAO;
			GLuint m_VBO;
			VertexData* m_Buffer;
			IndexBuffer* m_IBO;
			GLsizei m_IndexCount;
			void init();
		};


	}
}