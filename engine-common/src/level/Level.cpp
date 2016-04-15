#include "Level.h"

// static pointer to the current level
Level* Level::currentLevel;

Level::Level(LevelParams params) {
	m_Renderer = params.renderer;
}

Level::~Level() { }

bool Level::init() { return 0; }

bool Level::destroy() { return 0; }

void Level::update(float msec) {

	// UPDATE
	for (map<string, Entity*>::iterator it = m_Entities.begin(); it != m_Entities.end(); ++it) {
		(it->second)->update(msec);
	}

	// GAME LOGIC
	m_GameLogic->update(msec);

	// RENDER
	for (map<string, Entity*>::iterator it = m_Entities.begin(); it != m_Entities.end(); ++it) {
		(it->second)->render(m_Renderer);
	}

}