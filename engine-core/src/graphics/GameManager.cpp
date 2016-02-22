#include "GameManager.h"

namespace engine {
	namespace graphics {

		GameManager::GameManager()
			: window(Window(TITLE, WIDTH, HEIGHT)){
			renderer = Renderer();
			physicsManager = PhysicsManager();
			entities = vector<Entity*>();
		}

		GameManager::~GameManager() {
			if (!entities.empty()) {
				for (int i = 0; i < entities.size(); i++) {
					delete entities[i];
				}
			}
		}
		
		void GameManager::addEntity(Entity* e) {
			entities.push_back(e);
		}

		void GameManager::run() {
			while (!window.closed()) {
				window.clear();
				for (int i = 0; i < entities.size(); i++)
					entities[i]->update(timer.GetTimedMS());
				for (int i = 0; i < entities.size(); i++)
					entities[i]->render(&renderer);
				window.update();
			}
		}
	}
}