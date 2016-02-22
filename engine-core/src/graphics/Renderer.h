#pragma once

#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "RenderObject.h"

namespace engine {
	namespace graphics {

		class Renderer {
		public:
			Renderer();
			~Renderer();
			virtual void RenderScene();
			virtual void Render(RenderObject &o);
			virtual void UpdateScene(float msec);
			void AddRenderObject(RenderObject &r);
		protected:
			std::vector<RenderObject*> renderObjects;
			void UpdateShaderMatrices(GLuint shaderId);
		};


	}
}