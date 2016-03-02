#pragma once

#include <vector>
#include "../graphics/Entity.h"
#include "SceneLogic.h"

using std::vector;

class Scene
{
public:
	Scene();
	virtual ~Scene();
private:
	vector<Entity*> m_Entities;
	SceneLogic* m_SceneLogic;
};

