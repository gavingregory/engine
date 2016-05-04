/******************************************************************************
Class:Level
Author:Gavin Gregory
Description:The level class represents a level in the game. The main game loop 
calls update on the level, which in turn updates and renders each of its entities.
*//////////////////////////////////////////////////////////////////////////////

#pragma once

#include <Box2D/Box2D.h>
#include "../system/SubSystem.h"
#include <stack>
#include "../graphics/Entity.h"
#include "../../../engine-io/src/io/Loader.h"
#include "../../../engine-audio/src/Audio.h"
#include "../../../engine-common/src/game/BaseLogic.h"

using std::stack;

struct LevelParams {
	Renderer* renderer;
};

class Level : public SubSystem
{
public:
	Level(LevelParams params);
	virtual ~Level();
	bool init();
	bool destroy();
	void update(float msec);
	map<string, Entity*>* getEntities() { return &m_Entities; }
	map<string, Mesh*>* getMeshes() { return &m_Meshes; }
	map<string, Shader*>* getShaders() { return &m_Shaders; }
	map<string, GLuint>* getTextures() { return &m_Textures; }
	map<string, ISoundSource*>* getSounds() { return &m_Sounds; }
	void setLogic(BaseLogic* logic) { m_GameLogic = logic; }
	static stack<Level*> LevelStack;
	static Level* LoadLevel();
private:
	map<string, Entity*> m_Entities;
	map<string, Mesh*> m_Meshes;
	map<string, Shader*> m_Shaders;
	map<string, GLuint> m_Textures;
	map<string, ISoundSource*> m_Sounds;
	BaseLogic* m_GameLogic;
	Renderer* m_Renderer;
};