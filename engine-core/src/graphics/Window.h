#pragma once
#include <GL/glew.h>
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
	  void clear() const;
	  bool closed() const;

	  inline int getWidth() const { return m_Width; }
	  inline int getHeight() const { return m_Height; }

    };
  }
}