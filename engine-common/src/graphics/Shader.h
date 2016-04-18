/******************************************************************************
Class:Shader
Author:Rich Davison	<richard.davison4@newcastle.ac.uk>
Modified by Gavin Gregory
*//////////////////////////////////////////////////////////////////////////////

#pragma once

#include <string>
#include <iostream>
#include <fstream>

#include "GL/glew.h"
#include "Mesh.h"
#include <glm/ext.hpp>

using std::cout;
using std::endl;

enum ShaderStage {
	SHADER_VERTEX = 0,
	SHADER_FRAGMENT,
	SHADER_GEOMETRY,
	SHADER_TCS,
	SHADER_TES,
	SHADER_MAX
};

struct ShaderParams {
	string vertex;
	string fragment;
	string geometry;
	string tcs;
	string tes;
};

class Shader {
public:
	Shader(ShaderParams params);
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

