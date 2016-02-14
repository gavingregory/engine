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
	  -1.0f, -1.0f, 0.0f,
	   1.0f, -1.0f, 0.0f,
	   0.0f,  1.0f, 0.0f,
	 };

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// This will identify our vertex buffer
	GLuint vertexbuffer;
	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &vertexbuffer);
	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_triangle), vertices_triangle, GL_STATIC_DRAW);

	glm::mat4 ortho = glm::ortho(0.0f, 16.0f, 0.0f, 9.0f);
	glm::mat4 proj = glm::perspectiveFov(90.0f, 50.0f, 50.0f, -5.0f, -100.0f);

	Shader shader("src/shaders/BasicVert.glsl", "src/shaders/BasicFrag.glsl");
	shader.enable();
	//shader.setUniformMat4("projection", proj);
	//shader.setUniformMat4("model", glm::scale(glm::vec3(0.1f, 0.1f, 0.1f)));

	while (!window.closed())
	{
		window.clear();

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			   0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			   3,                  // size
			  GL_FLOAT,           // type
			   GL_FALSE,           // normalized?
			   0,                  // stride
			    (void*)0            // array buffer offset
			);
		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
		glDisableVertexAttribArray(0);

		window.update();
	}

	return 0;
}