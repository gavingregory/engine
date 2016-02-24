#include "GameManager.h"

namespace engine {
	namespace graphics {

		GameManager::GameManager()
			: m_Window(Window(TITLE, WIDTH, HEIGHT)){
			m_Renderer = Renderer();
			m_PhysicsManager = PhysicsManager();
			m_RenderObjects = vector<RenderObject*>();
			Window::WindowPointer = &m_Window;
		}

		GameManager::~GameManager() {
			if (!m_RenderObjects.empty()) {
				for (int i = 0; i < m_RenderObjects.size(); i++) {
					delete m_RenderObjects[i];
				}
			}
			Window::WindowPointer = nullptr;
		}
		
		void GameManager::addRenderObject(RenderObject* o) {
			m_RenderObjects.push_back(o);
		}

		void GameManager::run() {
			while (!m_Window.closed()) {
				m_Window.clear();
				for (int i = 0; i < m_RenderObjects.size(); i++)
					m_RenderObjects[i]->Update(m_Timer.GetTimedMS());
				for (int i = 0; i < m_RenderObjects.size(); i++)
					m_Renderer.Render(m_RenderObjects[i]);
				m_Window.update();
			}
		}
	}
}