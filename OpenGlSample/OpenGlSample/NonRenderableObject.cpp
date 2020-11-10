#include "NonRenderableObject.h"
#include "Renderer.h"

NonRenderableObject::NonRenderableObject()
{
	Renderer *renderer = Renderer::instance();
	renderer->addNonRenderObject(this);
}

void NonRenderableObject::init()
{

}

void NonRenderableObject::render()
{

}

void NonRenderableObject::Update()
{

}

void NonRenderableObject::shutDown()
{

}

void NonRenderableObject::setPosition(float x, float y, float z)
{

}
