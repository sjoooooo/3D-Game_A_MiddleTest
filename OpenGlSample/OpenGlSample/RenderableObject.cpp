#include "Renderer.h"
#include "RenderableObject.h"


RenderableObject::RenderableObject()
{
	Renderer* renderer = Renderer::instance();
	renderer->addObject(this);
}