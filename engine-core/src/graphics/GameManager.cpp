#include "GameManager.h"

GameManager::GameManager(GameManagerParams params)
	: m_Window(Window(params.title.c_str(), params.width, params.height)) {
	m_Renderer = new Renderer();
	m_Entities = vector<Entity*>();
	Window::WindowPointer = &m_Window;
	m_Camera = new Camera(0.0f, 0.0f, glm::vec3(0, 0, 300));
	Camera::width = 400.0f;
	Camera::vw_matrix = glm::lookAt(glm::vec3(0.f, 0.f, 3.0f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.0f, 1.0f, 0.0f));

	Camera::pr_matrix = glm::ortho(-(Camera::width/2), (Camera::width/2), -(Camera::width / 2), (Camera::width / 2), 0.0f, 100.0f);
	Camera::light_src = vec3(0, 0, 200);

	//m_Audio = new Audio();
	//if (!m_Audio->init()) cout << "Audio subsystem init failed." << endl;

	m_InputHandler = params.inputHandler;
	if (!m_InputHandler->init()) { cout << "Input Handler init failed!" << endl; exit(1); }

	m_MemoryManager = params.memoryManager;
	if (!m_MemoryManager->init()) { cout << "Memory manager init failed!" << endl; exit(1); }

	m_GameLogic = params.gameLogic;
	if (!m_GameLogic->init()) { cout << "Game logic init failed!" << endl; exit(1); }
}

GameManager::~GameManager() {
	Window::WindowPointer = nullptr;
	m_InputHandler->destroy();
	if (m_InputHandler) delete m_InputHandler;
	
	if (m_Camera) delete m_Camera;
	
	if (m_Renderer) delete m_Renderer;
	
	m_Audio->destroy();
	if (m_Audio) delete m_Audio;
	
	m_GameLogic->destroy();
	if (m_GameLogic) delete m_GameLogic;
	m_MemoryManager->destroy();

	m_MemoryManager->destroy();
	if (m_MemoryManager) delete m_MemoryManager;
	for (unsigned int i = 0; i < m_Entities.size(); i++)
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
		for (unsigned int i = 0; i < m_Entities.size(); i++)
			m_Entities[i]->update(msec);

		// COLLISION
		for (unsigned int i = 0; i < Entity::CollidingEntities.size(); i++) {
			for (unsigned int j = 0; j < Entity::CollidingEntities.size(); j++) {
				if (i != j) {
					if (!Entity::CollidingEntities[i]->getPhysicsObject()->isColliding(Entity::CollidingEntities[j]->getPhysicsObject())) {
						if (Physics::detectCollision(
							Entity::CollidingEntities[i]->getPhysicsObject()->m_Velocity, Entity::CollidingEntities[i]->getPhysicsObject()->m_Mass, Entity::CollidingEntities[i]->getPhysicsObject()->getCollisionShape(), Entity::CollidingEntities[i]->getPhysicsObject()->m_Position,
							Entity::CollidingEntities[j]->getPhysicsObject()->m_Velocity, Entity::CollidingEntities[j]->getPhysicsObject()->m_Mass, Entity::CollidingEntities[j]->getPhysicsObject()->getCollisionShape(), Entity::CollidingEntities[j]->getPhysicsObject()->m_Position,
							1.0f)) {
							Entity::CollidingEntities[i]->getPhysicsObject()->collide(Entity::CollidingEntities[j]->getPhysicsObject());
							Entity::CollidingEntities[j]->getPhysicsObject()->collide(Entity::CollidingEntities[i]->getPhysicsObject());
						}
					}
					else {
						Entity::CollidingEntities[i]->getPhysicsObject()->noCollide(Entity::CollidingEntities[j]->getPhysicsObject());
						Entity::CollidingEntities[j]->getPhysicsObject()->noCollide(Entity::CollidingEntities[i]->getPhysicsObject());
					}
				}
			}
		}

		// GAME LOGIC
		m_GameLogic->update(msec);

		// RENDER
		for (unsigned int i = 0; i < m_Entities.size(); i++)
			m_Entities[i]->render(m_Renderer);
		m_Window.update();
	}
}