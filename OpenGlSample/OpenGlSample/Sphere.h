#ifndef __SPHERE_H_
#define __SPHERE_H_

#include "RenderableObject.h"

class RenderableObject;
class FileManager;

class Sphere : public RenderableObject
{
public:
	Sphere();

	virtual void setPosition(float x, float y, float z) override;

	virtual void shutDown() override;

	virtual void Update() override;

};

#endif // !__SPHERE_H_