#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>

#define MAX_BUTTONS 32

class Window {
private:
    const char* m_Title;
    int m_Width, m_Height;
	GLFWwindow* m_Window;
	bool m_Closed;

	bool init();

	bool m_MouseButtons[MAX_BUTTONS];
	double m_MouseX, m_MouseY;
	float m_ScrollOffsetX, m_ScrollOffsetY;
	friend static void window_resize(GLFWwindow* window, int width, int height);
	friend static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	friend static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
	friend static void scroll_callback(GLFWwindow* window, double xOffset, double yOffset);


public:
    Window(const char* title, const int width, const int height);
    ~Window();
    void update();
	void clear() const;
	bool closed() const;

	inline int getWidth() const { return m_Width; }
	inline int getHeight() const { return m_Height; }

	inline int getMouseX() const { return m_MouseX; }
	inline int getMouseY() const { return m_MouseY; }

	GLFWwindow* getGlfwWindow() { return m_Window; }

	// gets a vector of the mouse position relative to the last time you called this function
	glm::vec2 getMouseOffset() const {
		static glm::vec2 previous = glm::vec2(m_MouseX, m_MouseY);
		glm::vec2 offset = previous - glm::vec2(m_MouseX, m_MouseY);
		previous = glm::vec2(m_MouseX, m_MouseY);
		std::cout << offset.x << ", " << offset.y << std::endl;
		return offset;
	}

	inline float getScrollOffsetX() const { return m_ScrollOffsetX; }
	inline float getScrollOffsetY() const { return m_ScrollOffsetY; }

	bool isMouseButtonPressed(const unsigned int keycode) const;
	bool isScrolled();

	static Window* WindowPointer;
};