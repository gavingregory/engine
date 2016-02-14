#include "src/graphics/Window.h"
#include "src/utils/File.h"
#include "src/graphics/Shader.h"
#include <iostream>
#include <glm/vec2.hpp>
#include <glm/ext.hpp> // to_string(v)!
#include <glm/gtc/type_ptr.hpp>
#include "src/graphics/buffers/Buffer.h"
#include "src/graphics/buffers/IndexBuffer.h"
#include "src/graphics/buffers/VertexArray.h"

int main()
{
	using namespace engine;
	using namespace graphics;

	Window window("OpenGL", 960, 540);
	glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

#if 0
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

#else 
	GLfloat vertices[] =
	{
		0, 0, 0,
		0, 3, 0,
		8, 3, 0,
		8, 0, 0,
	};

	GLushort indices[] = {
		0,1,2,
		2,3,0
	};

	GLfloat coloursA[] = {
		1,0,1,1,
		1,0,1,1,
		1,0,1,1,
		1,0,1,1
	};

	GLfloat coloursB[] = {
		0.2f, 0.3f, 0.8f, 1.0f,
		0.2f, 0.3f, 0.8f, 1.0f,
		0.2f, 0.3f, 0.8f, 1.0f,
		0.2f, 0.3f, 0.8f, 1.0f
	};

	VertexArray sprite1, sprite2; 
	IndexBuffer ibo(indices, 6);

	sprite1.addBuffer(new Buffer(vertices, 4 * 3, 3), 0);
	sprite1.addBuffer(new Buffer(coloursA, 4 * 4, 4), 1);

	sprite2.addBuffer(new Buffer(vertices, 4 * 3, 3), 0);
	sprite2.addBuffer(new Buffer(coloursB, 4 * 4, 4), 1);
#endif

	glm::mat4 ortho = glm::ortho(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

	Shader shader("src/shaders/BasicVert.glsl", "src/shaders/BasicFrag.glsl");
	shader.enable();
	shader.setUniformMat4("pr_matrix", ortho);
	shader.setUniformMat4("ml_matrix", glm::translate(glm::vec3(4,3,0)));

	shader.setUniform4f("colour", glm::vec4(0.2f, 0.3f, 0.8f, 1.0f));

	//glm::mat4 ortho = glm::ortho(-1.f, 1.f, -1.f, 1.f);
	//glm::mat4 proj = glm::perspectiveFov(60.0f, 50.0f, 50.0f, -5.0f, -100.0f);
	
	while (!window.closed())
	{
		window.clear();
		std::cout << window.getMouseX() << " " << window.getMouseY() << std::endl;
		shader.setUniform2f("light_pos", glm::vec2((float)(window.getMouseX() * 16.0f / 960.0f), (float)(9.0f - window.getMouseY() * 9.0f / 540.0f)));
#if 0
		glDrawArrays(GL_TRIANGLES, 0, 6);
#else
		sprite1.bind();
		ibo.bind();
		shader.setUniformMat4("ml_matrix", glm::translate(glm::vec3(4, 3, 0)));
		glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_SHORT, 0);
		ibo.unbind();
		sprite1.unbind();

		sprite2.bind();
		ibo.bind();
		shader.setUniformMat4("ml_matrix", glm::translate(glm::vec3(0, 0, 0)));
		glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_SHORT, 0);
		ibo.unbind();
		sprite2.unbind();
#endif
		window.update();
	}

	return 0;
}