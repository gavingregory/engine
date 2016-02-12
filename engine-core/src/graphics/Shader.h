#pragma once

#include <vector>
#include <iostream>
#include <GL/glew.h>
#include "../utils/File.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace engine {
	namespace graphics {

		class Shader
		{
		public:
			Shader(const char* vertexPath, const char* fragmentPath);
			virtual ~Shader();

			inline GLuint getShader() const { return m_ShaderId; }

			GLint getUniformLocation(const GLchar* name);

			void setUniformMat4(const GLchar* name, const glm::mat4& matrix);
			void setUniform1f(const GLchar* name, const float f);
			void setUniform2f(const GLchar* name, const glm::vec2& vec);
			void setUniform3f(const GLchar* name, const glm::vec3& vec);
			void setUniform4f(const GLchar* name, const glm::vec4& vec);
			void setUniform1i(const GLchar* name, const GLint integer);

			void enable();
			void disable();
		private:
			GLuint m_ShaderId;
			const char* m_VertexPath;
			const char* m_FragmentPath;
			GLuint load();
		};

	}
}