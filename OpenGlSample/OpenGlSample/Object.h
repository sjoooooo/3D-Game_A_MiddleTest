#ifndef __OBJECT_H__
#define __OBJECT_H__

#include "RenderableObject.h"

class Object : public RenderableObject
{

public:
	virtual void init() override;
	virtual void render() override;
	virtual void Update() override;
	virtual void shutDown() override;
	virtual void setPosition(float x, float y, float z) override;

};

#endif