#include "GameManager.h"

GameManager::GameManager(GameManagerParams params)
	: m_Window(Window(params.title.c_str(), params.width, params.height)) {
	m_Renderer = params.renderer;
	Window::WindowPointer = &m_Window;
	m_Camera = new Camera(vec3(0, 0, 300));
	Camera::width = 400.0f;
	Camera::vw_matrix = lookAt(vec3(0.f, 0.f, 3.0f), vec3(0.f, 0.f, 0.f), vec3(0.0f, 1.0f, 0.0f));

	Camera::pr_matrix = ortho(-(Camera::width/2), (Camera::width/2), -(Camera::width / 2), (Camera::width / 2), 0.0f, 100.0f);
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
}

void GameManager::run() {

	while (!m_Window.closed()) {
		m_Window.clear();

		float msec = m_Timer.GetTimedMS();

		// update camera
		//m_Camera->UpdateCamera(msec, m_InputHandler->getMouseRelative());
		//Camera::vw_matrix = m_Camera->BuildViewMatrix();

		if (m_InputHandler) m_InputHandler->handleInput(msec);

		// call update on the top level on the stack
		m_LevelStack.top()->update(msec);

		m_Window.update();
	}
}