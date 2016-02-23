#include "TableEntity.h"

TableEntity::TableEntity()
	: Entity(glm::vec3(0), glm::vec3(0), glm::vec3(0), RenderObject(), "table") {

}

TableEntity::TableEntity(glm::vec3 position, glm::vec3 velocity, glm::vec3 acceleration, RenderObject o, string name)
	: Entity(position, velocity, acceleration, o, name) {

}

TableEntity::~TableEntity() {}

void TableEntity::update(float msec) {
	renderObject.SetModelMatrix(glm::translate(*this->position));
	renderObject.Update(msec);
}