#include "RenderObject.h"

RenderObject::RenderObject() {
	mesh	= NULL;
	shader	= NULL;
	m_Textures = map<string, GLuint>();
	parent  = NULL;
}

RenderObject::RenderObject(RenderObjectParams params) {
	mesh = params.mesh;
	shader = params.shader;
	m_Textures = map<string, GLuint>();
	parent = NULL;
	modelMatrix = glm::translate(params.position);
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
	glUniform3f(glGetUniformLocation(shader->GetShaderProgram(), "light_src"), Camera::light_src.x, Camera::light_src.y, Camera::light_src.z);
	glUniform3f(glGetUniformLocation(shader->GetShaderProgram(), "camera_pos"), 0, 0, 300);
	//glUniform2f(glGetUniformLocation(shader->GetShaderProgram(), "light_src"), Camera::light_src.x, Camera::light_src.y);
}