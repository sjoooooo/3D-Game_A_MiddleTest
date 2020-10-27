#include "RenderableObject.h"


void RenderableObject::shutDown()
{
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &uvbuffer);
	glDeleteBuffers(1, &normalbuffer);
	glDeleteProgram(programID);
	glDeleteTextures(1, &Texture);
	glDeleteVertexArrays(1, &VertexArrayID);
}

void RenderableObject::SetPosition(float x, float y, float z)
{
	PosX = x, PosY = y, PosZ = z;
}

void RenderableObject::RotateObj(float angle, float R_x, float R_y, float R_z)
{
	glm::mat4 Rotation = glm::rotate(Rotation,angle, glm::vec3(R_x, R_y, R_z));
}
