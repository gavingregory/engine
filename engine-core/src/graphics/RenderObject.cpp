#include "RenderObject.h"

using namespace engine::graphics;

RenderObject::RenderObject(void) {
	mesh	= NULL;
	shader	= NULL;
	texture = vector<GLuint>();
	textureName = vector<string>();
	parent  = NULL;
}

RenderObject::RenderObject(Mesh*m, Shader*s) {
	mesh	= m;
	shader	= s;
	texture = vector<GLuint>();
	textureName = vector<string>();
	parent  = NULL;
}

RenderObject::RenderObject(Mesh*m, Shader*s, glm::vec3 pos) {
	mesh = m;
	shader = s;
	texture = vector<GLuint>();
	textureName = vector<string>();
	parent = NULL;
	modelMatrix = glm::translate(pos);
}

RenderObject::~RenderObject() { }

void RenderObject::Update(float msec) {
	if (parent) worldTransform = parent->modelMatrix * modelMatrix;
	else worldTransform = modelMatrix;
}

void RenderObject::Draw() const {
	if(mesh) mesh->Draw();
}

void RenderObject::UpdateShaderMatrices() {
	for (std::map<string, glm::vec4>::iterator it = m_UniformVec4.begin(); it != m_UniformVec4.end(); ++it)
		glUniform4f(glGetUniformLocation(shader->GetShaderProgram(), (it->first).c_str()), it->second.x, it->second.y, it->second.z, it->second.w);

	glUniformMatrix4fv(glGetUniformLocation(shader->GetShaderProgram(), "ml_matrix"), 1, GL_FALSE, glm::value_ptr(worldTransform));
	glUniformMatrix4fv(glGetUniformLocation(shader->GetShaderProgram(), "vw_matrix"), 1, GL_FALSE, glm::value_ptr(Camera::vw_matrix));
	glUniformMatrix4fv(glGetUniformLocation(shader->GetShaderProgram(), "pr_matrix"), 1, GL_FALSE, glm::value_ptr(Camera::pr_matrix));
}