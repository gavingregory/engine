#pragma once

#include "../../../engine-common/src/graphics/Entity.h"
#include "../../../engine-common/src/graphics/Window.h"
#include "BallEntity.h"

/**
* Pocket Entity Parameters (a struct of params used when constructing pocket entities)
*/
struct PocketEntityParams {
	vec3 position;
	vec3 velocity;
	vec3 acceleration;
	float rotation;
	float mass;
	Mesh* mesh;
	Shader* shader;
	string name;
	vec3 normal;
	vec3 distance;
};

class PocketEntity : public Entity
{
public:
	PocketEntity(PocketEntityParams params, RenderObject* ro, PhysicsObject* po, CollisionPlane* c);
	virtual ~PocketEntity();

	/**
	 * Collision event gets called when an entity has collided with another entity. This is used to perform
	 * any logic on entities.
	 */
	virtual void collisionEvent(Entity* other) override {
		if (BallEntity* b = dynamic_cast<BallEntity*>(other)) {
			// pocket has collided with a ball! remove it
			b->getRenderObject()->setDrawable(false);
			Entity::CollidingEntities.erase(
				std::remove(Entity::CollidingEntities.begin(), Entity::CollidingEntities.end(), b), Entity::CollidingEntities.end()
			);
		}
	}
};
