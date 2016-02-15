#pragma once

#include <GL/glew.h>

namespace engine {
	namespace graphics {

		class IndexBuffer
		{
		public:
			IndexBuffer(GLushort* data, GLsizei count);
			IndexBuffer(GLuint* data, GLsizei count);

			virtual ~IndexBuffer();

			inline GLuint getCount() const { return m_Count;  }

			void bind() const;
			void unbind() const;

		private:
			GLuint m_BufferId;
			GLuint m_Count; // count of indices
		};

	}
}
