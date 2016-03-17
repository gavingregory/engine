#include "NodeEntity.h"

NodeEntity::NodeEntity(NodeEntityParams params, RenderObject* ro)
	: Entity(EntityParams{params.position, params.velocity, params.acceleration, params.rotation, params.mass, params.mesh, params.shader, params.name}, ro) {
}

NodeEntity::~NodeEntity() {}