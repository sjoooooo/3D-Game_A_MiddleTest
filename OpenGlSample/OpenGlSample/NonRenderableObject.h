#ifndef __NONRENDERABLEOBJECT_H__
#define __NONRENDERABLEOBJECT_H__
#include "ObjectManager.h"
#include "IUpdater.h"

class NonRenderableObject : public ObjectManager
{
public:
	NonRenderableObject();

public:

	virtual void Update() override;
	virtual void setPosition(float x, float y, float z) override;
	virtual void render() override;
	virtual void init() override;
	virtual void shutDown() override;

};


#endif