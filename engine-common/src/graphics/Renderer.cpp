/******************************************************************************
Class:Renderer
Author:Rich Davison	<richard.davison4@newcastle.ac.uk>
Modified by Gavin Gregory
*//////////////////////////////////////////////////////////////////////////////

#include "Renderer.h"

Renderer::Renderer() { glEnable(GL_DEPTH_TEST); }

Renderer::~Renderer() { }

void Renderer::Render(RenderObject* o) {
	glUseProgram(o->GetShader()->GetShaderProgram());
	o->UpdateShaderMatrices();

	// bind textures, if any exist
	int index = 0;
	for (map<string, GLuint>::iterator it = o->getTextures()->begin(); it != o->getTextures()->end(); ++it) {
		glUniform1i(glGetUniformLocation(o->GetShader()->GetShaderProgram(), it->first.c_str()), index);
		glActiveTexture(GL_TEXTURE0 + index++);
		glBindTexture(GL_TEXTURE_2D, it->second);
	}

	// transparency stuff
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	o->Draw();
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Renderer::AddRenderObject(RenderObject &r) {
	renderObjects.push_back(&r);
}