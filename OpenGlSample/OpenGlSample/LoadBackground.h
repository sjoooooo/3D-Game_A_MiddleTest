#ifndef __LOADBACKGROUND_H_
#define __LOADBACKGROUND_H_

#include "RenderableObject.h"
#include "FileManager.h"
#include "Object.h"


class LoadBackground : public RenderableObject
{
public:
	LoadBackground(FileManager * filepath);

public:
	glm::vec3 BackgroundPos;

	float BackgroundX, BackgroundY, BackgroundZ;

	void SetBackgroundPosition(float x, float y, float z);

	virtual void shutDown() override;

};

#endif // !__LOADBACKGROUND_H_