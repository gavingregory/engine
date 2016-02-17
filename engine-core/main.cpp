#include "src/graphics/Window.h"
#include "src/graphics/Shader.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "src/graphics/buffers/buffer.h"
#include "src/graphics/buffers/indexbuffer.h"
#include "src/graphics/buffers/vertexarray.h"

#include <time.h>

#include "src/utils/Timer.h"

#include "src/physics/Physics.h"
#include "src/graphics/renderers/RenderObject.h"
#include "src/graphics/renderers/Renderer.h"

#define BATCH_RENDERER 1

int main()
{
	using namespace engine;
	using namespace graphics;
	using namespace utils;

	Window window("Engine", 960, 540);
	// glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glm::mat4 ortho = glm::ortho(0.0f, 16.0f, 0.0f, 9.0f, -100.0f, 100.0f);
	glm::mat4 projection = glm::perspective(45.0f, 960.0f / 540.0f, 1.0f, 100.0f);

	glm::mat4 ml_matrix = glm::translate(glm::vec3(0, 0, -5));

	//Mesh* mesh = Mesh::LoadMeshFile("src/meshes/cube.asciimesh");
	Mesh* mesh = Mesh::LoadMeshFile("src/meshes/cube.asciimesh");
	
	Shader* shader = new Shader("src/shaders/BasicVert.glsl", "src/shaders/BasicFrag.glsl");
	RenderObject o(mesh, shader, NULL, "texture");
	Renderer renderer = Renderer();

	renderer.AddRenderObject(o);

	while (!window.closed()) {
		window.clear();
		ml_matrix *= glm::rotate(0.0001f, glm::vec3(0, 0, 1));
		ml_matrix *= glm::rotate(0.0001f, glm::vec3(0, 1, 0));
		glUniformMatrix4fv(glGetUniformLocation(shader->GetShaderProgram(), "pr_matrix"), 1, false, glm::value_ptr(projection));
		glUniformMatrix4fv(glGetUniformLocation(shader->GetShaderProgram(), "ml_matrix"), 1, false, glm::value_ptr(ml_matrix));
		renderer.UpdateScene(1.0f);
		renderer.RenderScene();
		window.update();
	}

	return 0;
}