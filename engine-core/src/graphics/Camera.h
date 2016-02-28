#pragma once

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <algorithm>

namespace engine {
	namespace graphics {

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

		protected:
			float	yaw;
			float	pitch;
			glm::vec3 position;

		};

	}
}

