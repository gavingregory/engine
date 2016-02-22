#include "RenderObject.h"

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

RenderObject::~RenderObject() { }

void RenderObject::Update(float msec) {
	if (parent) worldTransform = parent->modelMatrix * modelMatrix;
	else worldTransform = modelMatrix;

	for(vector<RenderObject*>::const_iterator i = children.begin(); i != children.end(); ++i )
		(*i)->Update(msec);
}

void RenderObject::Draw() const {
	if(mesh) mesh->Draw();
}

void RenderObject::UpdateShaderMatrices() {
	glm::mat4 pr_matrix = glm::ortho(0.0f, 20.0f, 0.0f, 20.0f, -100.0f, 100.0f);
	glm::mat4 vw_matrix = glm::mat4(1.0f);
	glUniformMatrix4fv(glGetUniformLocation(shader->GetShaderProgram(), "ml_matrix"), 1, GL_FALSE, glm::value_ptr(worldTransform));
	glUniformMatrix4fv(glGetUniformLocation(shader->GetShaderProgram(), "vw_matrix"), 1, GL_FALSE, glm::value_ptr(vw_matrix));
	glUniformMatrix4fv(glGetUniformLocation(shader->GetShaderProgram(), "pr_matrix"), 1, GL_FALSE, glm::value_ptr(pr_matrix));
}