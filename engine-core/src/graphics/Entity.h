#pragma once

#include <glm/glm.hpp>
#include "RenderObject.h"
#include "PhysicsObject.h"
#include "Renderer.h"
#include "../../../engine-physics/src/Physics.h"

namespace engine {
	namespace graphics {
		using namespace glm;
		using namespace engine::physics;

		class Entity
		{
		public:
			Entity(vec3 p, vec3 v, vec3 a, Mesh* m, Shader* s, string n);
			virtual ~Entity();

			inline vec3 getPosition() const { return m_PhysicsObject->m_Position; }
			inline vec3 getAcceleration() const { return m_PhysicsObject->m_Acceleration; }
			inline vec3 getVelocity() const { return m_PhysicsObject->m_Velocity; }
			inline RenderObject* getRenderObject() const { return m_RenderObject; }
			inline PhysicsObject* getPhysicsObject() const { return m_PhysicsObject; }

			virtual void update(float dt);
			virtual void render(Renderer* renderer);

			void addChild(Entity* e);

		protected:
			string m_Name;
			RenderObject* m_RenderObject;
			PhysicsObject* m_PhysicsObject;
			Entity* parent;
			vector<Entity*> children;
		};

	}
}