#ifndef __OBJECT_H__
#define __OBJECT_H__

#include "RenderableObject.h"

class Object : public RenderableObject
{
public:
	glm::mat4 getMatrixTranslatePosition(glm::mat4 Model, RenderableObject *obj);

	virtual void init() override;
	virtual void render() override;
	virtual void Update() override;
	virtual void shutDown() override;
	virtual void setPosition(float x, float y, float z) override;
	virtual void setRot(float speed, float x, float y, float z)override;
	virtual void setScale(float x, float y, float z)override;
	virtual void setCameraPos(float x, float y, float z) override;


};

#endif