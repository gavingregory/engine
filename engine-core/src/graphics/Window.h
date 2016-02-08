#pragma once
#include <GLFW/glfw3.h>

namespace engine {
  namespace graphics {
    class Window {
    private:
      const char* m_Title;
      int m_Width, m_Height;
	  GLFWwindow* m_Window;

	  bool init();

    public:
      Window(const char* title, int width, int height);
      ~Window();
      void update();
	  bool closed() const;
    };
  }
}