#include "Gun.h"
#include "FileManager.h"
#include "KeyManager.h"

void Gun::init()
{
	KeyManager *keymgr = new KeyManager();
	FileManager *filemgr = FileManager::instance();

	filemgr->loadOBJs(this, "eagle.obj", "ironskin.bmp", "20161614_vs.shader", "20161614_fs.shader");

	this->setPosition(0.0f,0.0f,0.0f);
}

void Gun::setPosition(float x, float y, float z)
{
	PosX = x, PosY = y, PosZ = z;
}

void Gun::Update()
{

}

void Gun::render()
{
	// Use our shader
	glUseProgram(this->programID);

	KeyManager::GetInstance()->UseKeyBoard();

	glm::mat4 ProjectionMatrix = KeyManager::GetInstance()->getProjectionMatrix();
	glm::mat4 ViewMatrix = KeyManager::GetInstance()->getViewMatrix();

	glm::mat4 ModelMatrix = glm::mat4(1.0);

	glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

	// Send our transformation to the currently bound shader,
	// in the "MVP" uniform
	glUniformMatrix4fv(this->MatrixID, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(this->ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
	glUniformMatrix4fv(this->ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);

	glm::vec3 lightPos = glm::vec3(0, 10, 0);
	glUniform3f(this->LightID, lightPos.x, lightPos.y, lightPos.z);

	/*glm::vec3 lightPos2 = glm::vec3(0, 0, 10);
	glUniform3f(src_obj->LightID2, lightPos2.x, lightPos2.y, lightPos2.z);*/

	// Bind our texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->Texture);
	// Set our "myTextureSampler" sampler to use Texture Unit 0
	glUniform1i(this->TextureID, 0);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, this->vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	// 2nd attribute buffer : UVs
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, this->uvbuffer);
	glVertexAttribPointer(
		1,                                // attribute
		2,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	// 3rd attribute buffer : normals
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, (unsigned)this->normalbuffer);
	glVertexAttribPointer(
		2,                                // attribute
		3,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	// Draw the triangles !
	glDrawArrays(GL_TRIANGLES, 0, (unsigned)this->vertices.size());

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}


void Gun::shutDown()
{
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &uvbuffer);
	glDeleteBuffers(1, &normalbuffer);
	glDeleteProgram(MatrixID);
	glDeleteProgram(programID);
	glDeleteVertexArrays(1, &VertexArrayID);
}

