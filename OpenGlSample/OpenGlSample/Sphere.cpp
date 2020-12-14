#include "Sphere.h"

Sphere::Sphere()
{
	FileManager *loadFile = FileManager::instance();

	programID = loadFile->LoadShaders("20161614_vs.shader", "20161614_fs.shader");

	Texture = loadFile->loadBMP("goldskin.BMP");

	TextureID = glGetUniformLocation(programID, "myTextureSampler");

	bool res = loadFile->loadOBJ("sphere.obj", vertices, uvs, normals);


	MatrixID = glGetUniformLocation(programID, "MVP");
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);

	glGenBuffers(1, &normalbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
}

void Sphere::setPosition(float x, float y, float z)
{
	PosX = x, PosY = y, PosZ = z;
}

void Sphere::shutDown()
{
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &uvbuffer);
	glDeleteBuffers(1, &normalbuffer);
	glDeleteProgram(programID);
	glDeleteTextures(1, &Texture);
	glDeleteVertexArrays(1, &VertexArrayID);
}

void Sphere::Update()
{

}

