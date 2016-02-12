#include "Window.h"
#include <iostream>

using namespace engine;
using namespace graphics;

void windowResize(GLFWwindow* window, int width, int height);

Window::Window(const char* title, int width, int height)
	: m_Title(title), m_Width(width), m_Height(height)
{
	if (!init())
		glfwTerminate();
}

Window::~Window()
{
	glfwTerminate();
}

void Window::update()
{
	glfwPollEvents();
	glfwSwapBuffers(m_Window);
}

bool Window::init()
{
	if (!glfwInit())
	{
		std::cout << "Failed to init GLFW" << std::endl;
		return false;
	}
	m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);
	if (!m_Window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		return false;
	}
	glfwMakeContextCurrent(m_Window);
	glfwSetWindowUserPointer(m_Window, this);
	glfwSetWindowSizeCallback(m_Window, windowResize);

	if (glewInit() != GLEW_OK) {
		std::cout << "Could not init GLEW" << std::endl;
		return false;
	}

	return true;
}

bool Window::closed() const
{
	return glfwWindowShouldClose(m_Window) == 1;
}
void Window::clear() const
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void windowResize(GLFWwindow* window, int width, int height)
{
	// TODO: as this function is not a member of the class, it does not update m_Width and m_Height
	glViewport(0, 0, width, height);
}