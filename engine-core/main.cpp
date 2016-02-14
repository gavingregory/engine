#include "src/graphics/Window.h"
#include "src/utils/File.h"
#include "src/graphics/Shader.h"
#include <iostream>
#include <glm/vec2.hpp>
#include <glm/ext.hpp> // to_string(v)!
#include <glm/gtc/type_ptr.hpp>


int main()
{
	using namespace engine;
	using namespace graphics;

	Window window("OpenGL", 800, 600);
	glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

	GLfloat vertices_cube[] = {
		 -1.0f,-1.0f,-1.0f, // triangle 1 : begin
		 -1.0f,-1.0f, 1.0f,
		 -1.0f, 1.0f, 1.0f, // triangle 1 : end
		  1.0f, 1.0f,-1.0f, // triangle 2 : begin
		 -1.0f,-1.0f,-1.0f,
		 -1.0f, 1.0f,-1.0f, // triangle 2 : end
		  1.0f,-1.0f, 1.0f,
		 -1.0f,-1.0f,-1.0f,
		  1.0f,-1.0f,-1.0f,
		  1.0f, 1.0f,-1.0f,
		  1.0f,-1.0f,-1.0f,
		 -1.0f,-1.0f,-1.0f,
		 -1.0f,-1.0f,-1.0f,
		 -1.0f, 1.0f, 1.0f,
		 -1.0f, 1.0f,-1.0f,
		  1.0f,-1.0f, 1.0f,
		 -1.0f,-1.0f, 1.0f,
		 -1.0f,-1.0f,-1.0f,
		 -1.0f, 1.0f, 1.0f,
		 -1.0f,-1.0f, 1.0f,
		  1.0f,-1.0f, 1.0f,
		  1.0f, 1.0f, 1.0f,
		  1.0f,-1.0f,-1.0f,
		  1.0f, 1.0f,-1.0f,
		  1.0f,-1.0f,-1.0f,
		  1.0f, 1.0f, 1.0f,
		  1.0f,-1.0f, 1.0f,
		  1.0f, 1.0f, 1.0f,
		  1.0f, 1.0f,-1.0f,
		 -1.0f, 1.0f,-1.0f,
		  1.0f, 1.0f, 1.0f,
		 -1.0f, 1.0f,-1.0f,
		 -1.0f, 1.0f, 1.0f,
		  1.0f, 1.0f, 1.0f,
		 -1.0f, 1.0f, 1.0f,
		  1.0f,-1.0f, 1.0f
		};
	static const GLfloat vertices_triangle[] = {
	  -1.0f, -1.0f, -5.0f,
	   1.0f, -1.0f, -5.0f,
	   0.0f,  1.0f, -5.0f,
	 };

	GLfloat vertices[] =
	{
		0, 0, 0,
		8, 0, 0,
		0, 3, 0,
		0, 3, 0,
		8, 3, 0,
		8, 0, 0
	};

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glm::mat4 ortho = glm::ortho(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

	Shader shader("src/shaders/BasicVert.glsl", "src/shaders/BasicFrag.glsl");
	shader.enable();
	shader.setUniformMat4("pr_matrix", ortho);
	shader.setUniformMat4("ml_matrix", glm::translate(glm::vec3(4, 3, 0)));

	shader.setUniform2f("light_pos", glm::vec2(4.0f, 1.5f));
	shader.setUniform4f("colour", glm::vec4(0.2f, 0.3f, 0.8f, 1.0f));

	//glm::mat4 ortho = glm::ortho(-1.f, 1.f, -1.f, 1.f);
	//glm::mat4 proj = glm::perspectiveFov(60.0f, 50.0f, 50.0f, -5.0f, -100.0f);
	
	while (!window.closed())
	{
		window.clear();
		std::cout << window.getMouseX() << " " << window.getMouseY() << std::endl;
		shader.setUniform2f("light_pos", glm::vec2((float)(window.getMouseX() * 16.0f / 960.0f), (float)(9.0f - window.getMouseY() * 9.0f / 540.0f)));
		glDrawArrays(GL_TRIANGLES, 0, 6);
		window.update();
	}

	return 0;
}