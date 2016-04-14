#include "Entity.h"

Entity::Entity(EntityParams params, RenderObject* ro) {
	m_RenderObject = ro;
	m_PhysicsObject = Physics::CurrentWorld->CreateBody(&params.bodyDef);
	m_PhysicsObject->SetUserData(this); // set a pointer to THIS entity

	// create FIXTURE for box 2d physics objects
	b2PolygonShape shape;
	shape.SetAsBox(params.width, params.height);
	m_PhysicsObject->CreateFixture(&shape, 1.0f);

	m_Name = params.name;
}

Entity::~Entity() { }

void Entity::update(float msec) {
	// update render object position from box2d position
	b2Vec2 pos = m_PhysicsObject->GetPosition();
	m_RenderObject->SetModelMatrix(translate(vec3(pos.x, pos.y, 0)));

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