#include "RenderObject.h"

RenderObject::RenderObject(void) {
	mesh	= NULL;
	shader	= NULL;
	texture = vector<GLuint>();
	textureName = vector<string>();
	parent  = NULL;
}

RenderObject::RenderObject(Mesh*m, Shader*s) {
	mesh	= m;
	shader	= s;
	texture = vector<GLuint>();
	textureName = vector<string>();
	parent  = NULL;
}

RenderObject::~RenderObject() { }

void RenderObject::Update(float msec) {
	if(parent) worldTransform = parent->modelMatrix * modelMatrix;
	else worldTransform = modelMatrix;

	for(vector<RenderObject*>::const_iterator i = children.begin(); i != children.end(); ++i )
		(*i)->Update(msec);
}

void RenderObject::Draw() const {
	if(mesh) mesh->Draw();
}