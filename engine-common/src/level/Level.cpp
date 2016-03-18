#include "Level.h"

// static pointer to the current level
Level* Level::currentLevel;

Level::Level(LevelParams params) :
	m_World(b2World(b2Vec2(params.gravity.x, params.gravity.y))) {
	Entity::currentWorld = &m_World; // set a static pointer to the current world
	m_Renderer = params.renderer;
}

Level::~Level() { }

bool Level::init() { return 0; }

bool Level::destroy() { return 0; }

void Level::update(float msec) {

	int32 velocityIterations = 6;
	int32 positionIterations = 2;
	
	// Advance Box2d world
	m_World.Step(msec, velocityIterations, positionIterations);

	// UPDATE
	for (map<string, Entity*>::iterator it = m_Entities.begin(); it != m_Entities.end(); ++it) {
		(it->second)->update(msec);
	}
	
	// RENDER
	for (map<string, Entity*>::iterator it = m_Entities.begin(); it != m_Entities.end(); ++it) {
		(it->second)->render(m_Renderer);
	}

	// GAME LOGIC
	//m_GameLogic->update(msec);
}