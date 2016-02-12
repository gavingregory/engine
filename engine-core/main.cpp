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

	std::string file = engine::utils::File::ReadTextFile("main.cpp");
	std::cout << file << std::endl;

	Window window("OpenGL", 800, 600);
	glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

	GLfloat vertices[] = {
		-0.5f, -0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f
		- 0.5f, -0.5f, 0.0f
	};

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glm::mat4 ortho = glm::ortho(0.0f, 16.0f, 0.0f, 9.0f);

	Shader shader("shaders/BasicVert.glsl", "shaders/BasicFrag.glsl");
	shader.enable();
	shader.setUniformMat4("pr_matrix", ortho);

	while (!window.closed())
	{
		window.clear();

		glDrawArrays(GL_TRIANGLES, 0, 6);

		window.update();
	}

	return 0;
}