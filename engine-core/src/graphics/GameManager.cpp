#include "GameManager.h"

namespace engine {
	namespace graphics {

		GameManager::GameManager()
			: m_Window(Window(TITLE, WIDTH, HEIGHT)){
			m_Renderer = new Renderer();
			m_Audio = new Audio();
			m_Entities = vector<Entity*>();
			m_InputHandler = nullptr;
			Window::WindowPointer = &m_Window;
			m_Camera = new Camera(0.0f, 0.0f, glm::vec3(0, 0, 300));
			Camera::vw_matrix = m_Camera->BuildViewMatrix();
			Camera::pr_matrix = glm::perspective(45.0f, 800.0f / 600.0f, 1.0f, 1000.0f);
		}

		GameManager::~GameManager() {
			Window::WindowPointer = nullptr;
			if (m_InputHandler) delete m_InputHandler;
			if (m_Camera) delete m_Camera;
			if (m_Renderer) delete m_Renderer;
			for (int i = 0; i < m_Entities.size(); i++)
				delete m_Entities[i];
		}
		
		void GameManager::addEntity(Entity* e) {
			m_Entities.push_back(e);
		}

		void GameManager::run() {

			while (!m_Window.closed()) {
				m_Window.clear();
				
				float msec = m_Timer.GetTimedMS();

				// update camera
				//m_Camera->UpdateCamera(msec, m_InputHandler->getMouseRelative());
				//Camera::vw_matrix = m_Camera->BuildViewMatrix();

				if (m_InputHandler) m_InputHandler->handleInput(msec);

				// UPDATE
				for (int i = 0; i < m_Entities.size(); i++)
					m_Entities[i]->update(msec);

				for (int i = 0; i < m_Entities.size(); i++)
					for (int j = 0; j < m_Entities.size(); j++)
						if (i != j) {
							if (m_CollisionManager->detect((Circle*)m_Entities[i]->getPhysicsObject()->getCollisionShape(), (Circle*)m_Entities[j]->getPhysicsObject()->getCollisionShape()))
								std::cout << "Collision between " + m_Entities[i]->getName() << " and " << m_Entities[j]->getName() << std::endl;
						}

				// RENDER
				for (int i = 0; i < m_Entities.size(); i++)
					m_Entities[i]->render(m_Renderer);
				m_Window.update();
			}
		}
	}
}