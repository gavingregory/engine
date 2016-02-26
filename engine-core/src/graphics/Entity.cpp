#include "Entity.h"

namespace engine {
	namespace graphics {

		Entity::Entity(vec3 position, vec3 velocity, vec3 acceleration, Mesh* mesh, Shader* shader, string name) {
			m_RenderObject = new RenderObject(mesh, shader);
			m_PhysicsObject = new PhysicsObject(position, velocity, acceleration, m_RenderObject);
			m_Name = name;
		}

		Entity::~Entity() {
			if (m_RenderObject) delete m_RenderObject;
			if (m_PhysicsObject) delete m_PhysicsObject;
		}

		void Entity::update(float msec) {
			m_PhysicsObject->update(msec);
			m_RenderObject->Update(msec); // do i need this?
			for (int i = 0; i < children.size(); i++)
				children[i]->update(msec);
		}

		void Entity::render(Renderer* renderer) {
			renderer->Render(m_RenderObject);
			for (int i = 0; i < children.size(); i++)
				children[i]->render(renderer);
		}

		void Entity::addChild(Entity* e) {
			this->m_RenderObject->AddChild(e->m_RenderObject);
			this->children.push_back(e);
			e->parent = this;
		}
	}
}