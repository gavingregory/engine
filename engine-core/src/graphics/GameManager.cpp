#include "GameManager.h"

namespace engine {
	namespace graphics {

		GameManager::GameManager()
			: m_Window(Window(TITLE, WIDTH, HEIGHT)) {
			m_Renderer = new Renderer();

			m_Audio = new Audio();
			if (!m_Audio->init()) cout << "Audio subsystem init failed." << endl;

			m_Entities = vector<Entity*>();
			m_InputHandler = nullptr;
			Window::WindowPointer = &m_Window;
			m_Camera = new Camera(0.0f, 0.0f, glm::vec3(0, 0, 300));
			Camera::vw_matrix = m_Camera->BuildViewMatrix();
			Camera::pr_matrix = glm::perspective(45.0f, 800.0f / 600.0f, 1.0f, 1000.0f);
			Camera::light_src = vec3(0, 0, 200);

			m_MemoryManager = MemoryManager();
			m_MemoryManager.init();
		}

		GameManager::~GameManager() {
			Window::WindowPointer = nullptr;
			if (m_InputHandler) delete m_InputHandler;
			if (m_Camera) delete m_Camera;
			if (m_Renderer) delete m_Renderer;
			m_MemoryManager.destroy();
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

				for (int i = 0; i < m_Entities.size(); i++) {
					for (int j = 0; j < m_Entities.size(); j++) {
						if (i != j) {
							if (!m_Entities[i]->getPhysicsObject()->isColliding(m_Entities[j]->getPhysicsObject()))
							if (Physics::handleCollision(
								m_Entities[i]->getPhysicsObject()->m_Velocity, 1, (Circle*)m_Entities[i]->getPhysicsObject()->getCollisionShape(), m_Entities[i]->getPhysicsObject()->m_Position,
								m_Entities[j]->getPhysicsObject()->m_Velocity, 1, (Circle*)m_Entities[j]->getPhysicsObject()->getCollisionShape(), m_Entities[j]->getPhysicsObject()->m_Position,
								1.0f)) {
								m_Entities[i]->getPhysicsObject()->collide(m_Entities[j]->getPhysicsObject());
								m_Entities[j]->getPhysicsObject()->collide(m_Entities[i]->getPhysicsObject());
							}
							else {
								m_Entities[i]->getPhysicsObject()->noCollide(m_Entities[j]->getPhysicsObject());
								m_Entities[j]->getPhysicsObject()->noCollide(m_Entities[i]->getPhysicsObject());
							}


						}
					}
				}

				// RENDER
				for (int i = 0; i < m_Entities.size(); i++)
					m_Entities[i]->render(m_Renderer);
				m_Window.update();
			}
		}
	}
}