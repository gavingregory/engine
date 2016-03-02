#include "Camera.h"

glm::mat4 Camera::vw_matrix;
glm::mat4 Camera::pr_matrix;
glm::vec3 Camera::light_src;
float Camera::width;

Camera::Camera() {
	yaw = 0.0f;
	pitch = 0.0f;
};

Camera::Camera(float pitch, float yaw, glm::vec3 position) {
	this->pitch = pitch;
	this->yaw = yaw;
	this->position = position;
}

Camera::~Camera() {}

/*
Polls the camera for keyboard / mouse movement.
Should be done once per frame! Pass it the msec since
last frame (default value is for simplicities sake...)
*/
void Camera::UpdateCamera(float msec, glm::vec2 mouseRelative) {
	//Update the mouse by how much
	pitch += (mouseRelative.y) * 0.01f;
	yaw -= (mouseRelative.x) * 0.01f;

	//Bounds check the pitch, to be between straight up and straight down ;)
	pitch = std::min(pitch, 90.0f);
	pitch = std::max(pitch, -90.0f);

	if (yaw < 0) {
		yaw += 360.0f;
	}
	if (yaw > 360.0f) {
		yaw -= 360.0f;
	}

	msec *= 5.0f;
}

void Camera::UpdateCameraUp(float msec) {
	//position += glm::rotate(yaw, glm::vec3(0, 1, 0)) * glm::vec4(0, 0, -msec, msec);
}

void Camera::UpdateCameraDown(float msec) {
	//position -= glm::rotate(yaw, glm::vec3(0, 1, 0)) * glm::vec3(0, 0, -1) * msec;
}

void Camera::UpdateCameraLeft(float msec) {
	//position += glm::rotate(yaw, glm::vec3(0, 1, 0)) * glm::vec3(-1, 0, 0) * msec;
}

void Camera::UpdateCameraRight(float msec) {
	//position -= glm::rotate(yaw, glm::vec3(0, 1, 0)) * glm::vec3(-1, 0, 0) * msec;
}

/*
Generates a view matrix for the camera's viewpoint. This matrix can be sent
straight to the shader...it's already an 'inverse camera' matrix.
*/
glm::mat4 Camera::BuildViewMatrix() {
	//Why do a complicated matrix inversion, when we can just generate the matrix
	//using the negative values ;). The matrix multiplication order is important!
	return	glm::rotate(-pitch, glm::vec3(1, 0, 0)) *
		glm::rotate(-yaw, glm::vec3(0, 1, 0)) *
		glm::translate(-position);
};

vec2 Camera::calculateWorldPositionFromMouseCoords(vec2 mouseCoords) {
	vec2 position;
	
	position.x = mouseCoords.x / Window::Width;
	position.y = mouseCoords.y / Window::Height;

	position.x = position.x * (Camera::width * 2) - Camera::width;
	position.y = - (position.y * (Camera::width * 2) - Camera::width);
	
	return position;
}