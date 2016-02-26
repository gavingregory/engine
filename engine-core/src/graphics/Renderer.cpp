
#include "Renderer.h"


namespace engine {
	namespace graphics {


		Renderer::Renderer() { glEnable(GL_DEPTH_TEST); }

		Renderer::~Renderer() { }

		void Renderer::RenderScene() {
		}

		void Renderer::Render(RenderObject* o) {
			glUseProgram(o->GetShader()->GetShaderProgram());
			o->UpdateShaderMatrices();

			// transparency stuff
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			o->Draw();
			//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}

		void Renderer::UpdateScene(float msec) {
			cout << "SHOULD NOT BE IN THIS FUNCTION" << endl;
		}

		void Renderer::AddRenderObject(RenderObject &r) {
			renderObjects.push_back(&r);
		}

	}
}