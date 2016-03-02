#pragma once

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <algorithm>
#include "Window.h"

static const float PI = 3.14159265358979323846f;
static const float PI_OVER_360 = PI / 360.0f;

using glm::vec2;
using glm::vec3;
using glm::vec4;
using glm::mat4;

class Camera
{
public:
	Camera();

	Camera(float pitch, float yaw, glm::vec3 position);

	~Camera();

	void UpdateCamera(float msec, glm::vec2 mouseRelative);
	void UpdateCameraUp(float msec);
	void UpdateCameraDown(float msec);
	void UpdateCameraLeft(float msec);
	void UpdateCameraRight(float msec);

	//Builds a view matrix for the current camera variables, suitable for sending straight
	//to a vertex shader (i.e it's already an 'inverse camera matrix').
	glm::mat4 BuildViewMatrix();

	//Gets position in world space
	glm::vec3 GetPosition() const { return position; }
	//Sets position in world space
	void	SetPosition(glm::vec3 val) { position = val; }

	//Gets yaw, in degrees
	float	GetYaw()   const { return yaw; }
	//Sets yaw, in degrees
	void	SetYaw(float y) { yaw = y; }

	//Gets pitch, in degrees
	float	GetPitch() const { return pitch; }
	//Sets pitch, in degrees
	void	SetPitch(float p) { pitch = p; }

	static glm::mat4 pr_matrix;
	static glm::mat4 vw_matrix;
	static glm::vec3 light_src;
	static float width;

	static vec2 calculateWorldPositionFromMouseCoords(vec2 mouseCoords);

protected:
	float	yaw;
	float	pitch;
	glm::vec3 position;

};