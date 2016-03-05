#include "Entity.h"

Entity::Entity(EntityParams params, RenderObject* ro, PhysicsObject* po) {
	m_RenderObject = ro;
	m_PhysicsObject = po;
	m_Name = params.name;
}

Entity::~Entity() {
	if (m_RenderObject) delete m_RenderObject;
	if (m_PhysicsObject) delete m_PhysicsObject;
}

void Entity::update(float msec) {
	m_PhysicsObject->update(msec);
	m_RenderObject->Update(msec);
	for (unsigned int i = 0; i < children.size(); i++)
		children[i]->update(msec);
}

void Entity::render(Renderer* renderer) {
	renderer->Render(m_RenderObject);
	for (unsigned int i = 0; i < children.size(); i++)
		children[i]->render(renderer);
}

void Entity::addChild(Entity* e) {
	this->m_RenderObject->AddChild(e->m_RenderObject);
	this->children.push_back(e);
	e->parent = this;
}