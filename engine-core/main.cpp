#include "src/graphics/Window.h"
#include <iostream>



int main()
{
	using namespace engine;
	using namespace graphics;

	Window window("OpenGL", 800, 600);
	glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

	while (!window.closed())
	{
		window.clear();

		if (window.isKeyPressed(GLFW_KEY_A))
			std::cout << "pressed." << std::endl;
		if (window.isMouseButtonPressed(GLFW_MOUSE_BUTTON_1))
			std::cout << "button pressed." << std::endl;

		std::cout << window.getMouseX() << ", " << window.getMouseY() << std::endl;

		// to delete!
		glBegin(GL_QUADS);
		glVertex2f(-0.5f, -0.5f);
		glVertex2f(-0.5f,  0.5f);
		glVertex2f( 0.5f,  0.5f);
		glVertex2f( 0.5f, -0.5f);
		glEnd();
		// end to delete

		window.update();
	}

	return 0;
}