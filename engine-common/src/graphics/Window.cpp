#include "Window.h"
#include <iostream>

#include "glm/glm.hpp"

Window* Window::WindowPointer;
int Window::Width;
int Window::Height;
bool Window::quit = false;

Window::Window(const char* title, const int width, const int height)
	: m_Title(title) {
	Window::Width = width;
	Window::Height = height;	
	if (!init())
		glfwTerminate();
}

Window::~Window() {
	glfwTerminate();
}

void Window::update() {
	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
		std::cout << "OpenGL Error: " << error << std::endl;

	// reset scroll variables
	m_ScrollOffsetX /= 10;
	m_ScrollOffsetY /= 10;

	glfwPollEvents();
	glfwSwapBuffers(m_Window);
}

bool Window::init() {
	if (!glfwInit()) {
		std::cout << "Failed to init GLFW" << std::endl;
		return false;
	}
	m_Window = glfwCreateWindow(Window::Width, Window::Height, m_Title, NULL, NULL);
	if (!m_Window) {
		std::cout << "Failed to create GLFW window" << std::endl;
		return false;
	}
	glfwMakeContextCurrent(m_Window);
	glfwSetWindowUserPointer(m_Window, this);
	glfwSetWindowSizeCallback(m_Window, window_resize);
	glfwSetMouseButtonCallback(m_Window, mouse_button_callback);
	glfwSetCursorPosCallback(m_Window, cursor_position_callback);
	glfwSetInputMode(m_Window, GLFW_STICKY_KEYS, 1); // set sticky keys to ON, so that when we POLL the key presses we don't miss a key press
	glfwSetScrollCallback(m_Window, scroll_callback);
	glClearColor(0.f, 0.f, 0.f, 1.0f);
	// glfwSwapInterval(0.0f); // disable vsync

	if (glewInit() != GLEW_OK) {
		std::cout << "Could not init GLEW" << std::endl;
		return false;
	}

	std::cout << "OpenGL: " << glGetString(GL_VERSION) << std::endl;

	return true;
}

bool Window::closed() const {
	return glfwWindowShouldClose(m_Window) == 1;
}

void Window::clear() const {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void window_resize(GLFWwindow* window, int width, int height) {
	Window* win = (Window*)glfwGetWindowUserPointer(window);
	Window::Width = width;
	Window::Height = height;
	glViewport(0, 0, width, height);
	std::cout << "Window Resized: " << width << ", " << height << std::endl;
}

void scroll_callback(GLFWwindow* window, double xOffset, double yOffset) {
	Window* win = (Window*)glfwGetWindowUserPointer(window);
	win->m_ScrollOffsetX = (float)xOffset;
	win->m_ScrollOffsetY = (float)yOffset;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	Window* win = (Window*)glfwGetWindowUserPointer(window);
	win->m_MouseButtons[button] = action != GLFW_RELEASE;
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
	Window* win = (Window*)glfwGetWindowUserPointer(window);
	win->m_MouseX = xpos;
	win->m_MouseY = ypos;
}

bool Window::isMouseButtonPressed(const unsigned int button) const {
	if (button >= MAX_BUTTONS)
		return false;
	return m_MouseButtons[button];
}

bool Window::isScrolled() {
	if (abs(m_ScrollOffsetX) > 0.00001 || abs(m_ScrollOffsetY) > 0.00001)
		return true;
	return false;
}