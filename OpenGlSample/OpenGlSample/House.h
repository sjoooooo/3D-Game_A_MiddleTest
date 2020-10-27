#ifndef __HOUSE_H_
#define __HOUSE_H_

#include "RenderableObject.h"
#include "FileManager.h"
#include "Object.h"


class House : public RenderableObject
{
public:
	House(FileManager * filepath);

public:
	glm::vec3 SpherePos;

	float HouseX, HouseY, HouseZ;

	void SetHousePosition(float x, float y, float z);

	virtual void shutDown() override;

};

#endif // !__HOUSE_H_