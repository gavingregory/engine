#pragma once

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <algorithm>
#include "Window.h"

using glm::vec2;
using glm::vec3;
using glm::vec4;
using glm::mat4;

class Camera
{
public:
	Camera();
	Camera(vec3 position);
	~Camera();

	vec3 GetPosition() const { return position; }
	void SetPosition(const vec3 position) { this->position = position; }

	static mat4 pr_matrix;
	static mat4 vw_matrix;
	static vec3 light_src;
	static float width;

	static vec2 calculateWorldPositionFromMouseCoords(vec2 mouseCoords);

protected:
	vec3 position;

};