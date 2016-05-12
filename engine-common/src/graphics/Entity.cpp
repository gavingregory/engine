#include "Entity.h"

Entity::Entity(EntityParams params, RenderObject* ro) {
	m_RenderObject = ro;
	if (!params.hasPhysics) params.bodyDef.active = false;
	m_PhysicsObject = Physics::CurrentWorld->CreateBody(&params.bodyDef);
	m_PhysicsObject->SetUserData(this); // set a pointer to THIS entity
	// create FIXTURE for box 2d physics objects
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &params.shape;
	fixtureDef.isSensor = params.isSensor;
	fixtureDef.density = 1.0f;
	switch (params.category) {
	case EC_PLAYER:
		m_CollisionCategory = COLLISION_PLAYER;
		m_MaskBits = COLLISION_WALL | COLLISION_ENEMY | COLLISION_TRIGGER | COLLISION_OTHER;
		break;
	case EC_ENEMY:
		m_CollisionCategory = COLLISION_ENEMY;
		m_MaskBits = COLLISION_PLAYER;
		break;
	case EC_PLATFORM:
		m_CollisionCategory = COLLISION_WALL;
		m_MaskBits = COLLISION_PLAYER;
		break;
	case EC_TRIGGER:
		m_CollisionCategory = COLLISION_TRIGGER;
		m_MaskBits = COLLISION_PLAYER;
		break;
	}
	fixtureDef.filter.categoryBits = m_CollisionCategory;
	fixtureDef.filter.maskBits = m_MaskBits;
	m_PhysicsObject->CreateFixture(&fixtureDef);
	m_Name = params.name;
	m_Category = params.category;
}

Entity::~Entity() { }

void Entity::update(float msec) {
	// update render object position from box2d position
	b2Vec2 pos = m_PhysicsObject->GetPosition();
	float angle = m_PhysicsObject->GetAngle();
	m_RenderObject->SetModelMatrix(translate(vec3(pos.x, pos.y, 0)) * glm::rotate(angle, vec3(0, 0, 1)));

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