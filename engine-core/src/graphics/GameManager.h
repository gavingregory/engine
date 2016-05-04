/******************************************************************************
Class:GameManager
Author:Gavin Gregory
Description:The main game manager holds instances of all sub systems and contains
the main game loop.
*//////////////////////////////////////////////////////////////////////////////

#pragma once

#include <stack>
#include <string>
#include <stack>
#include "../../../engine-common/src/graphics/Renderer.h"
#include "../../../engine-common/src/graphics/Entity.h"
#include "../../../engine-common/src/utils/GameTimer.h"
#include "../../../engine-common/src/input/InputHandler.h"
#include "../../../engine-audio/src/Audio.h"
#include "../../../engine-common/src/system/SubSystem.h"
#include "../../../engine-common/src/graphics/Camera.h"
#include "../../../engine-memory/src/MemoryManager.h"

#define WIDTH 800
#define HEIGHT 600
#define TITLE "The Engine"

struct GameManagerParams {
	MemoryManager* memoryManager;
	InputHandler* inputHandler;
	BaseLogic* gameLogic;
	Audio* audio;
	Physics* physics;
	Renderer* renderer;
	string title;
	int width;
	int height;
};

using std::stack;
using glm::ortho;

class GameManager
{
public:
	GameManager(GameManagerParams params);
	virtual ~GameManager();
	Audio* getAudio() const { return m_Audio; }
	MemoryManager* getMemoryManager() const { return m_MemoryManager; }
	Audio* getAudioManager() const { return m_Audio; }
	Camera* getCamera() const { return m_Camera; }
	void init();
	void run();
	void Shutdown();
private:
	Window m_Window;
	Renderer* m_Renderer;
	GameTimer m_Timer;
	InputHandler* m_InputHandler;
	MemoryManager* m_MemoryManager;
	BaseLogic* m_GameLogic;
	Audio* m_Audio;
	Camera* m_Camera;
	Physics* m_Physics;
};