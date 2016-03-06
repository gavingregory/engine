#include "Camera.h"

mat4 Camera::vw_matrix;
mat4 Camera::pr_matrix;
vec3 Camera::light_src;
float Camera::width;

Camera::Camera()
	: position(vec3(0)) { }

Camera::Camera(vec3 position)
	: position(position) { }

Camera::~Camera() {}

vec2 Camera::calculateWorldPositionFromMouseCoords(vec2 mouseCoords) {
	vec2 position;
	
	position.x = (float)mouseCoords.x / (float)Window::Width;
	position.y = (float)mouseCoords.y / (float)Window::Height;

	position.x = position.x * Camera::width - (Camera::width/2);
	position.y = - (position.y * Camera::width - (Camera::width/2));
	
	return position;
}