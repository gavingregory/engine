
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
}

void Renderer::UpdateScene(float msec) {

}

void Renderer::AddRenderObject(RenderObject &r) {
	renderObjects.push_back(&r);
}