#ifndef __RENDERABLEOBJECT_H__
#define __RENDERABLEOBJECT_H__

#include "CompositeObject.h"
#include <vector>


class RenderableObject : public CompositeObject
{

public:
	RenderableObject();

	virtual void init() override {};
	virtual void shutDown() override {};
	virtual void Update() override {};
	virtual void render() override {};

	virtual void setPosition(float x, float y, float z) {};
	virtual void setRot(float speed, float x, float y, float z) {};
	virtual void setScale(float x, float y, float z) {};
	virtual void setCameraPos(float x, float y, float z) {};

	virtual void AddChild(CompositeObject* addObj) override {};

	GLuint VertexArrayID;
	GLuint programID;
	GLuint MatrixID;
	GLuint ViewMatrixID;
	GLuint ModelMatrixID;
	GLuint Texture;
	GLuint TextureID;

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;

	GLuint vertexbuffer;
	GLuint uvbuffer;
	GLuint normalbuffer;
	GLuint LightID;

public:
	// 설정할 좌표를 받아올 X Y Z
	float PosX, PosY, PosZ;

};

#endif