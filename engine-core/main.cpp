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

#include "src/graphics/Renderer2d.h"
#include "src/graphics/SimpleRenderer2d.h"

#include "src/graphics/StaticSprite.h"

int main()
{
	using namespace engine;
	using namespace graphics;

	Window window("OpenGL", 960, 540);
	glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

	glm::mat4 ortho = glm::ortho(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

	Shader shader("src/shaders/BasicVert.glsl", "src/shaders/BasicFrag.glsl");
	shader.enable();
	shader.setUniformMat4("pr_matrix", ortho);
	shader.setUniformMat4("ml_matrix", glm::translate(glm::vec3(4,3,0)));

	StaticSprite sprite(5,5, 4,4, glm::vec4(1,0,1,1), shader);

	StaticSprite sprite2(7, 1, 2,3, glm::vec4(0.2f, 0, 1, 1), shader);


	SimpleRenderer2d renderer;

	shader.setUniform4f("colour", glm::vec4(0.2f, 0.3f, 0.8f, 1.0f));

	//glm::mat4 ortho = glm::ortho(-1.f, 1.f, -1.f, 1.f);
	//glm::mat4 proj = glm::perspectiveFov(60.0f, 50.0f, 50.0f, -5.0f, -100.0f);
	
	while (!window.closed())
	{
		window.clear();
		std::cout << window.getMouseX() << " " << window.getMouseY() << std::endl;
		shader.setUniform2f("light_pos", glm::vec2((float)(window.getMouseX() * 16.0f / 960.0f), (float)(9.0f - window.getMouseY() * 9.0f / 540.0f)));

		renderer.submit(&sprite);
		renderer.submit(&sprite2);
		renderer.flush();

		window.update();
	}

	return 0;
}