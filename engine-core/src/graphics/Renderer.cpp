
#include "Renderer.h"


namespace engine {
	namespace graphics {


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
		void Renderer::UpdateShaderMatrices(GLuint shaderId) {
			glm::mat4 pr_matrix = glm::ortho(0.0f, 20.0f, 0.0f, 20.0f, -100.0f, 100.0f);
			glm::mat4 vw_matrix = glm::mat4(1.0f);
			glm::mat4 ml_matrix = glm::translate(glm::vec3(5, 5, 5));
			glUniformMatrix4fv(glGetUniformLocation(shaderId, "ml_matrix"), 1, GL_FALSE, glm::value_ptr(ml_matrix));
			glUniformMatrix4fv(glGetUniformLocation(shaderId, "vw_matrix"), 1, GL_FALSE, glm::value_ptr(vw_matrix));
			glUniformMatrix4fv(glGetUniformLocation(shaderId, "pr_matrix"), 1, GL_FALSE, glm::value_ptr(pr_matrix));
		}

		void Renderer::UpdateScene(float msec) {

		}

		void Renderer::AddRenderObject(RenderObject &r) {
			renderObjects.push_back(&r);
		}

	}
}