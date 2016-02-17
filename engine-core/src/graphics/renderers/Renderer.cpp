
#include "Renderer.h"

Renderer::Renderer() { glEnable(GL_DEPTH_TEST); }

Renderer::~Renderer() { }

void Renderer::RenderScene() {
	for (std::vector<RenderObject*>::iterator i = renderObjects.begin(); i != renderObjects.end(); ++i) {
		Render(*(*i));
	}
}

void Renderer::Render(RenderObject &o) {
	glUseProgram(o.GetShader()->GetShaderProgram());
	UpdateShaderMatrices(o.GetShader()->GetShaderProgram());

	// transparency stuff
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	o.Draw();
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}


/*
Updates the uniform matrices of the current shader. Assumes that
the shader has uniform matrices called modelMatrix, viewMatrix,
projMatrix, and textureMatrix. Updates them with the relevant
matrix data. Sanity checks currentShader, so is always safe to
call.
*/
void Renderer::UpdateShaderMatrices(GLuint program) {
	//TODO: something with shader matrices!
}

void Renderer::UpdateScene(float msec) {

}

void Renderer::AddRenderObject(RenderObject &r) {
	renderObjects.push_back(&r);
}