#include "Entity.h"
#include "Window.h"

namespace engine {
	namespace graphics {
		//TODO: allocate memory in array or something
		Entity::Entity()
			: position(new vec3(0)), velocity(new vec3(0)), acceleration(new vec3(0)) {
			renderObject = RenderObject();
		}

		Entity::Entity(vec3 position, vec3 velocity, vec3 acceleration, RenderObject o)
			: position(new vec3(position)), velocity(new vec3(velocity)), acceleration(new vec3(acceleration)) {
			renderObject = o;
		}

		Entity::~Entity() {
			delete position;
			delete velocity;
			delete acceleration;
		}

		void Entity::update(float msec) {

			if (Window::WindowPointer->isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT)) {
				*acceleration = vec3(-0.001f, 0.0f, 0.0f);
				*velocity = vec3(0.1f, 0.0f, 0.0f);
			}

			*velocity = Physics::updateVelocity(*velocity, *acceleration, msec);
			
			*position += Physics::updateDisplacement(*velocity, *acceleration, msec);

			// slow down
			if ((*velocity).x < 0.0001f && (*velocity).y < 0.0001f && (*velocity).z < 0.0001f) {
				*acceleration = vec3(0);
				*velocity = vec3(0);
			}

			renderObject.SetModelMatrix(glm::translate(*this->position));
			renderObject.Update(msec);
		}

		void Entity::render(Renderer* renderer) {
			renderer->Render(renderObject);
		}

	}
}