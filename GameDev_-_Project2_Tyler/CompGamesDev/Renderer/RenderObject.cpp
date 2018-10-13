#include "RenderObject.h"



RenderObject::RenderObject()
{
	mesh = NULL;
	shader = NULL;
	tex = NULL;
	parent = NULL;
}

RenderObject::RenderObject(Mesh * m, Shader * s, GLuint t)
{
	mesh = m;
	shader = s;
	tex = t;
	parent = NULL;
}


RenderObject::~RenderObject()
{
}

void RenderObject::Update(float msec)
{
	if (parent) {
		worldTransform = parent->modelMatrix * modelMatrix;
	}
	else {
		worldTransform = modelMatrix;
	}

	for (vector<RenderObject*>::const_iterator i = children.begin(); i != children.end(); ++i) {
		(*i)->Update(msec);
	}

}

void RenderObject::Draw() const
{
	if (mesh) {
		mesh->Draw();
	}
}
