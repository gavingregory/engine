#pragma once

#include "../graphics/Window.h"
#include "PhysicsManager.h"
#include "Renderer.h"
#include "Entity.h"
#include "../utils/GameTimer.h"
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

			void addEntity(Entity* e);
			void run();
		private:
			Window window;
			PhysicsManager physicsManager;
			Renderer renderer;
			vector<Entity*> entities;
			GameTimer timer;
		};

	}
}