#include "Entity.h"

namespace engine {
	namespace graphics {
		//TODO: allocate memory in array or something
		Entity::Entity()
			: position(new vec3(0)), velocity(new vec3(0)), acceleration(new vec3(0)) {
			renderObject = new RenderObject();
		}

		Entity::Entity(vec3 position, vec3 velocity, vec3 acceleration)
			: position(new vec3(position)), velocity(new vec3(velocity)), acceleration(new vec3(acceleration)) {
			renderObject = new RenderObject();
		}

		Entity::~Entity() {
			delete position;
			delete velocity;
			delete acceleration;
			delete renderObject;
		}

	}
}