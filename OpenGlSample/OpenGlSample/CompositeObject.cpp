#include "CompositeObject.h"
#include <iostream>

CompositeObject::CompositeObject()
{
	child = new std::vector<CompositeObject*>();
	Parent = nullptr;
}

CompositeObject::~CompositeObject()
{
	for (
		std::vector<CompositeObject*>::const_iterator it = child->begin();
		it != child->end();
		++it
		)
	{
		delete (*it);
	}

	child->clear();

	delete child;
}


void CompositeObject::AddChild(CompositeObject* addObj)
{
	child->push_back(addObj);

	addObj->Parent = this;
}

void CompositeObject::Update()
{
	if (Parent)
	{
		WorldTransform = Parent->WorldTransform * Transform;
	}
	else
	{
		WorldTransform = Transform;
	}
}