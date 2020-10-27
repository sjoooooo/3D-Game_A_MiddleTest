#ifndef __RENDERABLEOBJECT_H__
#define __RENDERABLEOBJECT_H__

#include "Object.h"


class RenderableObject : public Object
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
	// vec3의 좌표를 받아올 Position
	glm::vec3 Position;

	// 설정할 좌표를 받아올 X Y Z
	float PosX, PosY, PosZ;

	// 오브젝트의 좌표를 설정
	void SetPosition(float x, float y, float z);

	// 오브젝트의 회전각도를 설정
	void RotateObj(float angle, float R_x, float R_y, float R_z);

	float MoveSpeed = 1.0f;

public:
	virtual void shutDown() override;

};

#endif