#ifndef __SPHERE_H_
#define __SPHERE_H_

#include "RenderableObject.h"
#include "FileManager.h"
#include "Object.h"


class Sphere : public RenderableObject
{
public:
	Sphere(FileManager * filepath);

public:
	glm::vec3 SpherePos;

	float SphereX, SphereY, SphereZ;

	void SetSpherePosition(float x, float y, float z);

	virtual void shutDown() override;

	virtual void Update() override;

};

#endif // !__SPHERE_H_