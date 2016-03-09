#pragma once

#include "../system/SubSystem.h"
#include "../graphics/Entity.h"
#include "../../../engine-audio/src/Audio.h"
#include "../../../engine-common/src/game/GameLogic.h"

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
private:
	map<string, Entity*> m_Entities;
	map<string, Mesh*> m_Meshes;
	map<string, Shader*> m_Shaders;
	map<string, GLuint> m_Textures;
	map<string, ISoundSource*> m_Sounds;
	GameLogic* m_GameLogic;
	Renderer* m_Renderer;

};