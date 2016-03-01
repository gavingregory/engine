#include "Entity.h"

Entity::Entity(EntityParams params) {
	RenderObjectParams roParams;
	roParams.mesh = params.mesh;
	roParams.shader = params.shader;
	roParams.position = params.position;
	m_RenderObject = new RenderObject(roParams);
	PhysicsObjectParams poParams;
	poParams.acceleration = params.acceleration;
	poParams.position = params.position;
	poParams.renderObject = m_RenderObject;
	poParams.velocity = params.velocity;
	poParams.collisionShape = nullptr;
	m_PhysicsObject = new PhysicsObject(poParams);
	m_Name = params.name;
}

Entity::~Entity() {
	if (m_RenderObject) delete m_RenderObject;
	if (m_PhysicsObject) delete m_PhysicsObject;
}

void Entity::update(float msec) {
	m_PhysicsObject->update(msec);
	m_RenderObject->Update(msec);
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