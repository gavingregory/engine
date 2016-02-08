#include <iostream>
#include <GLFW/glfw3.h>
#include "src/graphics/Window.h"

int main()
{

	using namespace engine;
	using namespace graphics;

	Window window("OpenGL", 800, 600);

	while (!window.closed())
	{
		window.update();
	}

	system("PAUSE");
	return 0;
}