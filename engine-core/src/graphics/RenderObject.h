#pragma once

#include <glm/glm.hpp>
#include <vector>
#include "Mesh.h"
#include "Shader.h"

class RenderObject	{
public:
	RenderObject();
	RenderObject(Mesh* m, Shader* s, GLuint t, string tName);
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
	glm::mat4 GetModelMatrix() const { return modelMatrix; }

	virtual void Update(float msec);

	virtual void Draw() const;

	void AddChild(RenderObject &child) {
		children.push_back(&child);
		child.parent = this;
	}

	glm::mat4 GetWorldTransform() const {
		return worldTransform;
	}

	const vector<RenderObject*>& GetChildren() const  {
		return children;
	}

protected:
	Mesh*	mesh;
	Shader*	shader;

	vector<GLuint> texture;
	vector<string> textureName;

	glm::mat4 modelMatrix;
	glm::mat4 worldTransform;

	RenderObject*			parent;
	vector<RenderObject*>	children;

};

