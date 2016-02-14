#pragma once

#include <GL/glew.h>

namespace engine {
	namespace graphics {

		class Buffer
		{
		public:
			Buffer(GLfloat* data, GLsizei count, GLuint componentCount);
			virtual ~Buffer();

			void bind() const;
			void unbind() const;

			inline GLuint getComponentCount() const { return m_ComponentCount; }

		private:
			GLuint m_BufferId;
			GLuint m_ComponentCount; // 1,2,3 items per 'object', etc
		};

	}
}
