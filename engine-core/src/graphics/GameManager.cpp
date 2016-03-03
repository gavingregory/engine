#include "GameManager.h"

GameManager::GameManager(GameManagerParams params)
	: m_Window(Window(params.title.c_str(), params.width, params.height)) {
	m_Renderer = new Renderer();
	m_Audio = new Audio();
	if (!m_Audio->init()) cout << "Audio subsystem init failed." << endl;
	m_Entities = vector<Entity*>();
	Window::WindowPointer = &m_Window;
	m_Camera = new Camera(0.0f, 0.0f, glm::vec3(0, 0, 300));
	Camera::width = 400.0f;
	Camera::vw_matrix = glm::lookAt(glm::vec3(0.f, 0.f, 3.0f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.0f, 1.0f, 0.0f));

	Camera::pr_matrix = glm::ortho(-(Camera::width/2), (Camera::width/2), -(Camera::width / 2), (Camera::width / 2), 0.0f, 100.0f);
	Camera::light_src = vec3(0, 0, 200);

	m_InputHandler = params.inputHandler;
	if (!m_InputHandler->init()) std::cout << "Input Handler init failed!" << std::endl;

	m_MemoryManager = params.memoryManager;
	if (!m_MemoryManager->init()) std::cout << "Memory manager init failed!" << std::endl;
}

GameManager::~GameManager() {
	Window::WindowPointer = nullptr;
	if (m_InputHandler) delete m_InputHandler;
	if (m_Camera) delete m_Camera;
	if (m_Renderer) delete m_Renderer;
	if (m_Audio) delete m_Audio;
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
		for (unsigned int i = 0; i < PhysicsObject::m_Colliders.size(); i++) {
			for (unsigned int j = 0; j < PhysicsObject::m_Colliders.size(); j++) {
				if (i != j) {
					if (!PhysicsObject::m_Colliders[i]->isColliding(PhysicsObject::m_Colliders[j])) {
						if (Physics::detectCollision(
							PhysicsObject::m_Colliders[i]->m_Velocity, PhysicsObject::m_Colliders[i]->m_Mass, (CollisionCircle*)PhysicsObject::m_Colliders[i]->getCollisionShape(), PhysicsObject::m_Colliders[i]->m_Position,
							PhysicsObject::m_Colliders[j]->m_Velocity, PhysicsObject::m_Colliders[j]->m_Mass, (CollisionCircle*)PhysicsObject::m_Colliders[j]->getCollisionShape(), PhysicsObject::m_Colliders[j]->m_Position,
							1.0f)) {
							cout << "collision " << endl;
							PhysicsObject::m_Colliders[i]->collide(PhysicsObject::m_Colliders[j]);
							PhysicsObject::m_Colliders[j]->collide(PhysicsObject::m_Colliders[i]);
						}
					}
					else {
						PhysicsObject::m_Colliders[i]->noCollide(PhysicsObject::m_Colliders[j]);
						PhysicsObject::m_Colliders[j]->noCollide(PhysicsObject::m_Colliders[i]);
					}

				}
			}
		}

		// RENDER
		for (unsigned int i = 0; i < m_Entities.size(); i++)
			m_Entities[i]->render(m_Renderer);
		m_Window.update();
	}
}