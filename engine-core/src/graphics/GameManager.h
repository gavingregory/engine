#pragma once

#include "../../../engine-common/src/graphics/Renderer.h"
#include "../../../engine-common/src/graphics/Entity.h"
#include "../../../engine-common/src/utils/GameTimer.h"
#include "../../../engine-common/src/input/InputHandler.h"
#include "../../../engine-audio/src/Audio.h"
#include "../../../engine-common/src/system/SubSystem.h"
#include "../../../engine-common/src/graphics/Camera.h"
#include <stack>
#include "../../../engine-memory/src/MemoryManager.h"

#define WIDTH 800
#define HEIGHT 600
#define TITLE "The Engine"

struct GameManagerParams {
	MemoryManager* memoryManager;
	InputHandler* inputHandler;
};

class GameManager
{
public:
	GameManager(GameManagerParams params);
	virtual ~GameManager();
	void addEntity(Entity* e);
	Audio* getAudio() const { return m_Audio; }
	MemoryManager* getMemoryManager() const { return m_MemoryManager; }
	Camera* getCamera() const { return m_Camera; }
	void run();

private:
	Window m_Window;
	Renderer* m_Renderer;
	vector<Entity*> m_Entities;
	GameTimer m_Timer;
	InputHandler* m_InputHandler;
	MemoryManager* m_MemoryManager;
	Audio* m_Audio;
	Camera* m_Camera;

};