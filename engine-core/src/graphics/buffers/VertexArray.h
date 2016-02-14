#pragma once

#include <GL/glew.h>
#include <vector>
#include "Buffer.h"

namespace engine {
	namespace graphics {

		class VertexArray
		{
		public:
			VertexArray();
			virtual ~VertexArray();

			void addBuffer(Buffer* buffer, GLuint index);

			void bind() const;
			void unbind() const;

		private:
			GLuint m_ArrayId;
			std::vector<Buffer*> m_Buffers;
		};

	}
}