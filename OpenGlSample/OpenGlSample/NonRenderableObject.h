#ifndef __NONRENDERABLEOBJECT_H__
#define __NONRENDERABLEOBJECT_H__
#include "Object.h"
#include "IUpdater.h"

class NonRenderableObject : public Object, public IUpdater
{
public:

	virtual void Update(IUpdater* Iupdater) override;
	virtual void shutDown() override;

};


#endif