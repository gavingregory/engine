#include "src/graphics/Window.h"
#include "src/graphics/Shader.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <time.h>

#include "src/utils/Timer.h"

#include "src/physics/Physics.h"
#include "src/graphics/renderers/RenderObject.h"
#include "src/graphics/renderers/Renderer.h"

#include "src/graphics/Entity.h"

#define WIDTH 800
#define HEIGHT 600

int main()
{
	using namespace engine;
	using namespace graphics;
	using namespace utils;
	using namespace glm;

	Window window("Engine", WIDTH, HEIGHT);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	mat4 ortho = glm::ortho(0.0f, 20.0f, 0.0f, 20.0f, -100.0f, 100.0f);
	mat4 projection = glm::perspective(70.0f, (float) window.getWidth() / window.getHeight(), 1.0f, 1000.0f);

	mat4 ml_matrix = translate(vec3(0, 0, -2));
	mat4 vw_matrix = translate(vec3(0, 0, -25));

	//Mesh* mesh = Mesh::GenerateCircle(0.5f, 30, vec4(1, 0, 0, 1));
	Mesh* tableMesh = Mesh::GenerateQuad(15,10, vec4(0.0f,1.f,0.0f,1));
	Mesh* ballMesh = Mesh::GenerateCircle(0.1f, 30, vec4(1.f, 0.0f, 0.0f, 1));
	//Mesh* mesh = Mesh::LoadMeshFile("src/meshes/cube.asciimesh");
	
	Shader* shader = new Shader("src/shaders/BasicVert.glsl", "src/shaders/BasicFrag.glsl");
	RenderObject tableObject(tableMesh, shader, NULL, "texture");
	RenderObject ballObject(ballMesh, shader, NULL, "texture");
	Renderer renderer = Renderer();

	Entity e(vec3(), vec3(), vec3(), ballObject);
	
	renderer.AddRenderObject(e.getRenderObject());

	while (!window.closed()) {
		window.clear();
		projection = glm::perspective(70.0f, (float)window.getWidth() / window.getHeight(), 1.0f, 1000.0f);
		//vw_matrix *= rotate(0.0001f, vec3(1, 0, 0));
		if (window.isKeyPressed(GLFW_KEY_W))
			ml_matrix *= translate(vec3(0, 0.01, 0));
		if (window.isKeyPressed(GLFW_KEY_S))
			ml_matrix *= translate(vec3(0, -0.01, 0));
		if (window.isKeyPressed(GLFW_KEY_A))
			ml_matrix *= translate(vec3(-0.01, 0, 0));
		if (window.isKeyPressed(GLFW_KEY_D))
			ml_matrix *= translate(vec3(0.01, 0, 0));
		if (window.isKeyPressed(GLFW_KEY_Q))
			ml_matrix *= translate(vec3(0, 0, -0.01));
		if (window.isKeyPressed(GLFW_KEY_E))
			ml_matrix *= translate(vec3(0, 0, 0.01));
		if (window.isScrolled())
			ml_matrix *= translate(vec3(0, 0, window.getScrollOffsetY()));

		glUniform2f(glGetUniformLocation(shader->GetShaderProgram(), "light_pos"), window.getMouseX() *20 / window.getHeight(), window.getMouseY() *20 / window.getWidth());
		glUniformMatrix4fv(glGetUniformLocation(shader->GetShaderProgram(), "pr_matrix"), 1, false, value_ptr(projection));
		glUniformMatrix4fv(glGetUniformLocation(shader->GetShaderProgram(), "ml_matrix"), 1, false, value_ptr(ml_matrix));
		glUniformMatrix4fv(glGetUniformLocation(shader->GetShaderProgram(), "vw_matrix"), 1, false, value_ptr(vw_matrix));
		renderer.UpdateScene(1.0f);
		renderer.RenderScene();
		window.update();
	}

	return 0;
}