#include "Shader.h"


namespace engine {
	namespace graphics {

		Shader::Shader(const char* vertexPath, const char* fragmentPath)
			: m_VertexPath(vertexPath), m_FragmentPath(fragmentPath) {
			m_ShaderId = load();
			std::cout << m_ShaderId << std::endl;
		}

		Shader::~Shader() {
			glDeleteProgram(m_ShaderId);
		}

		GLuint Shader::load() {
			GLuint program = glCreateProgram();

			GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
			GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

			std::string vertexString = engine::utils::File::ReadTextFile(m_VertexPath);
			std::string fragmentString = engine::utils::File::ReadTextFile(m_FragmentPath);

			const char* vertexSrc = vertexString.c_str();
			const char* fragmentSrc = fragmentString.c_str();

			glShaderSource(vertex, 1, &vertexSrc, NULL);
			glCompileShader(vertex);

			GLint result;
			glGetShaderiv(vertex, GL_COMPILE_STATUS, &result);

			if (result == GL_FALSE) {
				GLint length;
				glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length);
				std::vector<char> error(length);
				glGetShaderInfoLog(vertex, length, &length, &error[0]);
				std::cout << &error[0] << std::endl;
				glDeleteShader(vertex);
				return 0;
				// TODO: throw error?
			}

			glShaderSource(fragment, 1, &fragmentSrc, NULL);

			glCompileShader(fragment);

			glGetShaderiv(fragment, GL_COMPILE_STATUS, &result);

			if (result == GL_FALSE) {
				GLint length;
				glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &length);
				std::vector<char> error(length);
				glGetShaderInfoLog(fragment, length, &length, &error[0]);
				std::cout << &error[0] << std::endl;
				glDeleteShader(fragment);
				return 0;
				// TODO: throw error?
			}

			glAttachShader(program, vertex);
			glAttachShader(program, fragment);
			glLinkProgram(program);
			glValidateProgram(program);
			
			glDeleteShader(vertex);
			glDeleteShader(fragment);

			return program;
		}

		GLint Shader::getUniformLocation(const GLchar* name) {
			return glGetUniformLocation(m_ShaderId, name);
		}

		void Shader::setUniformMat4(const GLchar* name, const glm::mat4& matrix) {
			glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
		}

		void Shader::setUniform1f(const GLchar* name, const float f) {
			glUniform1f(getUniformLocation(name), f);
		}

		void Shader::setUniform2f(const GLchar* name, const glm::vec2& vec) {
			glUniform2f(getUniformLocation(name), vec[0], vec[1]);
		}

		void Shader::setUniform3f(const GLchar* name, const glm::vec3& vec) {
			glUniform3f(getUniformLocation(name), vec[0], vec[1], vec[2]);
		}

		void Shader::setUniform4f(const GLchar* name, const glm::vec4& vec) {
			glUniform4f(getUniformLocation(name), vec[0], vec[1], vec[2], vec[3]);
		}

		void Shader::setUniform1i(const GLchar* name, const GLint integer) {
			glUniform1i(getUniformLocation(name), integer);
		}

		void Shader::enable() {
			glUseProgram(m_ShaderId);
		}

		void Shader::disable() {
			glUseProgram(0);
		}

	}
}