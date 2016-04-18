/******************************************************************************
Class:Renderer
Author:Rich Davison	<richard.davison4@newcastle.ac.uk>
Modified by Gavin Gregory
*//////////////////////////////////////////////////////////////////////////////

#pragma once

#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "RenderObject.h"

class Renderer {
public:
	Renderer();
	~Renderer();
	virtual void Render(RenderObject* o);
	void AddRenderObject(RenderObject &r);
protected:
	std::vector<RenderObject*> renderObjects;
};