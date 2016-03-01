/******************************************************************************
Class:Shader
Implements:
Author:Rich Davison	<richard.davison4@newcastle.ac.uk>
Description:VERY simple class to encapsulate GLSL shader loading, linking,
and binding. Useful additions to this class would be overloaded functions to
replace the glUniformxx functions in external code, and possibly a map to store
uniform names and their resulting bindings.

-_-_-_-_-_-_-_,------,
_-_-_-_-_-_-_-|   /\_/\   NYANYANYAN
-_-_-_-_-_-_-~|__( ^ .^) /
_-_-_-_-_-_-_-""  ""

*//////////////////////////////////////////////////////////////////////////////

#pragma once


#include <string>
#include <iostream>
#include <fstream>

#include "GL/glew.h"
#include "Mesh.h"
#include <glm/ext.hpp>

enum ShaderStage {
	SHADER_VERTEX = 0,
	SHADER_FRAGMENT,
	SHADER_GEOMETRY,
	SHADER_TCS,
	SHADER_TES,
	SHADER_MAX
};

using namespace std;
class Shader {
public:
	Shader(string vertex, string fragment, string geometry = "", string tcs = "", string tes = "");
	~Shader();
	inline GLuint GetShaderProgram() const { return shaderId; }
	inline bool	ShaderLinked() const { return linkSuccess; }
	bool LinkProgram();

	GLint getUniformLocation(const GLchar* name);

	void setUniformMat4(const GLchar* name, const glm::mat4& matrix);
	void setUniform1f(const GLchar* name, const float f);
	void setUniform2f(const GLchar* name, const glm::vec2& vec);
	void setUniform3f(const GLchar* name, const glm::vec3& vec);
	void setUniform4f(const GLchar* name, const glm::vec4& vec);
	void setUniform1i(const GLchar* name, const GLint integer);

protected:
	bool LoadShaderFile(string from, string &into);
	GLuint GenerateShader(string from, GLenum type);
	void SetDefaultAttributes();
	GLuint objects[SHADER_MAX];
	GLuint shaderId;
	bool loadSuccess;
	bool linkSuccess;
};

