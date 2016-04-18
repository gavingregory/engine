/******************************************************************************
Class:RendeObject
Author:Rich Davison	<richard.davison4@newcastle.ac.uk>
Modified by Gavin Gregory
*//////////////////////////////////////////////////////////////////////////////


#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <map>
#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"

using glm::vec3;
using glm::vec4;
using std::vector;
using std::map;
using std::pair;

struct RenderObjectParams {
	vec3 position;
	Mesh* mesh;
	Shader* shader;
};

class RenderObject	{
public:
	RenderObject();
	RenderObject(RenderObjectParams params);
	~RenderObject();
	Mesh* GetMesh() const { return mesh; }
	void SetMesh(Mesh*m) { mesh = m; }
	inline Shader* GetShader() const { return shader; }
	inline void SetShader(Shader*s) { shader = s; }
	inline map<string, GLuint>* getTextures() { return &m_Textures; }
	inline void SetModelMatrix(glm::mat4 mat) { modelMatrix = mat; }
	inline glm::mat4 GetModelMatrix() const { return modelMatrix; }
	void pushUniformVec4(string name, glm::vec4 u) { m_UniformVec4.insert(pair<string, vec4>(name, u)); }
	virtual void Update(float msec);
	virtual void Draw() const;

	void UpdateShaderMatrices();

	void AddChild(RenderObject* child) {
		child->parent = this;
	}

	inline glm::mat4 GetWorldTransform() const { return worldTransform; }

protected:
	Mesh*	mesh;
	Shader*	shader;
	map<string, GLuint> m_Textures;
	glm::mat4 modelMatrix;
	glm::mat4 worldTransform;

	RenderObject*			parent;

	// a map of vector 4 uniforms
	map<string, glm::vec4> m_UniformVec4;

};

