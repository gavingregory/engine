#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <map>
#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"

class RenderObject	{
public:
	RenderObject();
	RenderObject(Mesh* m, Shader* s);
	RenderObject(Mesh* m, Shader* s, glm::vec3 pos);
	~RenderObject();
	Mesh* GetMesh() const { return mesh; }
	void SetMesh(Mesh*m) { mesh = m; }
	inline Shader* GetShader() const { return shader; }
	inline void SetShader(Shader*s) { shader = s; }
	inline string GetTextureNames(int index) const { return textureName[index]; }
	inline GLuint GetTextures(int index) const { return texture[index]; }
	inline int GetTexturesSize() const { return texture.size();  }
	inline void pushTexture(GLuint texture, string tName) { this->texture.push_back(texture); this->textureName.push_back(tName); }
	inline void SetModelMatrix(glm::mat4 mat) { modelMatrix = mat; }
	inline glm::mat4 GetModelMatrix() const { return modelMatrix; }
	void pushUniformVec4(string name, glm::vec4 u) { m_UniformVec4.insert(std::pair<string, glm::vec4>(name, u)); }
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

	vector<GLuint> texture;
	vector<string> textureName;

	glm::mat4 modelMatrix;
	glm::mat4 worldTransform;

	RenderObject*			parent;

	// a map of vector 4 uniforms
	map<string, glm::vec4> m_UniformVec4;

};

