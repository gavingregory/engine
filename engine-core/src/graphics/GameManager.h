#pragma once

#include "Renderer.h"
#include "Entity.h"
#include "../utils/GameTimer.h"
#include "../input/InputHandler.h"
#include "../../../engine-audio/src/Audio.h"
#include "../../../engine-physics/src/CollisionManager.h"
#include "Camera.h"
#include <stack>

#define WIDTH 800
#define HEIGHT 600
#define TITLE "The Engine"

namespace engine {
	namespace graphics {
		using namespace utils;

		class GameManager
		{
		public:
			GameManager();
			virtual ~GameManager();

			void addEntity(Entity* e);
			void setInputHandler(InputHandler* i) { m_InputHandler = i; }
			void run();

		private:
			Window m_Window;
			Renderer* m_Renderer;
			CollisionManager* m_CollisionManager;
			vector<Entity*> m_Entities;
			GameTimer m_Timer;
			InputHandler* m_InputHandler;
			Audio* m_Audio;
			Camera* m_Camera;
		};

	}
}