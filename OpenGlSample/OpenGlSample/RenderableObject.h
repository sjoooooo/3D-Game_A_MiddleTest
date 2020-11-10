#ifndef __RENDERABLEOBJECT_H__
#define __RENDERABLEOBJECT_H__

#include "ObjectManager.h"
#include <vector>

class RenderableObject : public ObjectManager
{
public:
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

public:
	RenderableObject();


public:
	virtual void init() override {};
	virtual void shutDown() override {};
	virtual void Update() override {};
	virtual void render() override {};
	virtual void setPosition(float x, float y, float z) override {};

};

#endif