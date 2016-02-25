#include "GameManager.h"

namespace engine {
	namespace graphics {

		GameManager::GameManager()
			: m_Window(Window(TITLE, WIDTH, HEIGHT)){
			m_Renderer = Renderer();
			m_PhysicsManager = PhysicsManager();
			m_RenderObjects = vector<RenderObject*>();
			m_InputHandler = nullptr;
			Window::WindowPointer = &m_Window;
			m_Camera = new Camera(0, 270.0f, glm::vec3(0, 0, 300));
			Camera::vw_matrix = m_Camera->BuildViewMatrix();
			Camera::pr_matrix = glm::perspective(45.0f, 800.0f / (float)600, 1.0f, 1000.0f);//glm::(-180.0f, 180.0f, -180.0f, 180.0f, -100.0f, 100.0f);
		}

		GameManager::~GameManager() {
			if (!m_RenderObjects.empty()) {
				for (int i = 0; i < m_RenderObjects.size(); i++) {
					delete m_RenderObjects[i];
				}
			}
			Window::WindowPointer = nullptr;
			if (m_InputHandler) delete m_InputHandler;
			if (m_Camera) delete m_Camera;
		}
		
		void GameManager::addRenderObject(RenderObject* o) {
			m_RenderObjects.push_back(o);
		}

		void GameManager::run() {
			while (!m_Window.closed()) {
				m_Window.clear();
				
				float msec = m_Timer.GetTimedMS();

				// update camera
				m_Camera->UpdateCamera(msec, m_InputHandler->getMouseRelative());
				Camera::vw_matrix = m_Camera->BuildViewMatrix();

				if (m_InputHandler) m_InputHandler->handleInput(msec);

				for (int i = 0; i < m_RenderObjects.size(); i++)
					m_RenderObjects[i]->Update(msec);
				for (int i = 0; i < m_RenderObjects.size(); i++)
					m_Renderer.Render(m_RenderObjects[i]);
				m_Window.update();
			}
		}
	}
}