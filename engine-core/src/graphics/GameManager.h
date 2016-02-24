#pragma once

#include "PhysicsManager.h"
#include "Renderer.h"
#include "RenderObject.h"
#include "../utils/GameTimer.h"
#include "../input/InputHandler.h"
#include "Camera.h"

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

			void addRenderObject(RenderObject* e);
			void setInputHandler(InputHandler* i) { m_InputHandler = i; }
			void run();

		private:
			Window m_Window;
			PhysicsManager m_PhysicsManager;
			Renderer m_Renderer;
			vector<RenderObject*> m_RenderObjects;
			GameTimer m_Timer;
			InputHandler* m_InputHandler;
			Camera* m_Camera;
		};

	}
}