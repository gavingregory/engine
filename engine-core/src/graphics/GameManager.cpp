#include "GameManager.h"

namespace engine {
	namespace graphics {

		GameManager::GameManager()
			: m_Window(Window(TITLE, WIDTH, HEIGHT)){
			m_Renderer = Renderer();
			m_PhysicsManager = PhysicsManager();
			m_Entities = vector<Entity*>();
			Window::WindowPointer = &m_Window;
		}

		GameManager::~GameManager() {
			if (!m_Entities.empty()) {
				for (int i = 0; i < m_Entities.size(); i++) {
					delete m_Entities[i];
				}
			}
			Window::WindowPointer = nullptr;
		}
		
		void GameManager::addEntity(Entity* e) {
			m_Entities.push_back(e);
		}

		void GameManager::run() {
			while (!m_Window.closed()) {
				m_Window.clear();
				for (int i = 0; i < m_Entities.size(); i++)
					m_Entities[i]->update(m_Timer.GetTimedMS());
				for (int i = 0; i < m_Entities.size(); i++)
					m_Entities[i]->render(&m_Renderer);
				m_Window.update();
			}
		}
	}
}