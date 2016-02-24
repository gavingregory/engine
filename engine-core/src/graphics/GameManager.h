#pragma once

#include "../graphics/Window.h"
#include "PhysicsManager.h"
#include "Renderer.h"
#include "RenderObject.h"
#include "../utils/GameTimer.h"

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
			void run();

		private:
			Window m_Window;
			PhysicsManager m_PhysicsManager;
			Renderer m_Renderer;
			vector<RenderObject*> m_RenderObjects;
			GameTimer m_Timer;
		};

	}
}