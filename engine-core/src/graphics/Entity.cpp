#include "Entity.h"

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

		void Entity::update(float dt) {
			renderObject.Update(dt);
		}

		void Entity::render() {
			//TODO: should this be here?
			renderObject.Draw();
		}

	}
}