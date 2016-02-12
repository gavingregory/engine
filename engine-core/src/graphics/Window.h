#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define MAX_KEYS 1024
#define MAX_BUTTONS 32

namespace engine {
  namespace graphics {

    class Window {
    private:
      const char* m_Title;
      int m_Width, m_Height;
	  GLFWwindow* m_Window;
	  bool m_Closed;

	  bool init();

	  static bool m_Keys[MAX_KEYS];
	  static bool m_MouseButtons[MAX_BUTTONS];
	  static double mx, my;
	  friend static void window_resize(GLFWwindow* window, int width, int height);
	  friend static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	  friend static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

    public:
      Window(const char* title, int width, int height);
      ~Window();
      void update();
	  void clear() const;
	  bool closed() const;

	  inline int getWidth() const { return m_Width; }
	  inline int getHeight() const { return m_Height; }

	  static bool isKeyPressed(unsigned int keycode);
	  static bool isMouseButtonPressed(unsigned int keycode);

    };
  }
}