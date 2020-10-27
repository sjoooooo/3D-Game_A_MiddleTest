#include <stdio.h>

#include "Object.h"
#include "Renderer.h"
#include "RenderableObject.h"
#include "NonRenderableObject.h"

#include "include/GL/glew.h"
#include "include/GLFW/glfw3.h" 
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

void Renderer::init()
{
	// Initialise GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		getchar();
		return;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	window = glfwCreateWindow(1024, 768, " 20161614 ", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		getchar();
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Set the mouse at the center of the screen
	glfwPollEvents();
	glfwSetCursorPos(window, 1024 / 2, 768 / 2);

	// Dark blue background
	glClearColor(0.2f, 0.2f, 0.2f, 0.0f);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);
}

void Renderer::render(RenderableObject* src_obj)
{
	// Use our shader
	glUseProgram(src_obj->programID);

	// glfwGetTime is called only once, the first time this function is called
	static double lastTime = glfwGetTime();

	// Compute time difference between current and last frame
	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);

	// Get mouse position
	double xpos, ypos;
	glfwGetCursorPos(GetWindow(), &xpos, &ypos);

	// 마우스 커서 숨기기
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	// Reset mouse position for next frame
	glfwSetCursorPos(GetWindow(), 1024 / 2, 768 / 2);

	// Compute new orientation
	horizontalAngle += MouseSpeed * float(1024 / 2 - xpos);
	verticalAngle += MouseSpeed * float(768 / 2 - ypos);

	glm::vec3 direction(
		cos(verticalAngle) * sin(horizontalAngle),
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);

	// Right vector
	glm::vec3 right = glm::vec3(
		sin(horizontalAngle - 3.14f / 2.0f),
		0,
		cos(horizontalAngle - 3.14f / 2.0f)
	);

	// Up vector
	glm::vec3 up = glm::cross(right, direction);

	// Move forward
	if (glfwGetKey(GetWindow(), GLFW_KEY_W) == GLFW_PRESS) {
		position += direction * deltaTime * MoveSpeed;
	}
	// Move backward
	if (glfwGetKey(GetWindow(), GLFW_KEY_S) == GLFW_PRESS) {
		position -= direction * deltaTime * MoveSpeed;
	}
	// Strafe right
	if (glfwGetKey(GetWindow(), GLFW_KEY_D) == GLFW_PRESS) {
		position += right * deltaTime * MoveSpeed;
	}
	// Strafe left
	if (glfwGetKey(GetWindow(), GLFW_KEY_A) == GLFW_PRESS) {
		position -= right * deltaTime * MoveSpeed;
	}

	float FoV = initialFoV;

	glm::mat4 MovePos = glm::mat4(1.0f);
	MovePos = glm::translate(MovePos, src_obj->Position);

	glm::mat4 RotatePos = glm::mat4(1.0f);
	RotatePos = glm::rotate(RotatePos, (90.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	glm::mat4 ScalePos = glm::mat4(1.0f);
	ScalePos = glm::scale(ScalePos, glm::vec3(2.0f, 2.0f, 2.0f));

	glm::mat4 MoveCameraPos = glm::mat4(1.0f);
	MoveCameraPos = glm::translate(MoveCameraPos, CameraPos);

	// Compute the MVP matrix from keyboard and mouse input // 45.0f
	glm::mat4 ProjectionMatrix = glm::perspective(glm::radians(FoV), 4.0f / 3.0f, 0.1f, 100.0f);
	// Camera matrix
	//glm::mat4 ViewMatrix = glm::lookAt(
	//	glm::vec3(0, 5, 7), // Camera is at (4,3,3), in World Space
	//	glm::vec3(0, 0, 0), // and looks at the origin
	//	glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
	glm::mat4 ViewMatrix = glm::lookAt(
		position,           // Camera is here
		position + direction, // and looks here : at the same position, plus "direction"
		up                  // Head is up (set to 0,-1,0 to look upside-down)
	);

	// For the next frame, the "last time" will be "now"
	lastTime = currentTime;

	glm::mat4 ModelMatrix = glm::mat4(1.0);
	ModelMatrix = getPosition(ModelMatrix, src_obj);

	glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

	// Send our transformation to the currently bound shader,
	// in the "MVP" uniform
	glUniformMatrix4fv(src_obj->MatrixID, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(src_obj->ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
	glUniformMatrix4fv(src_obj->ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);

	glm::vec3 lightPos = glm::vec3(0, 10, 0);
	glUniform3f(src_obj->LightID, lightPos.x, lightPos.y, lightPos.z);

	/*glm::vec3 lightPos2 = glm::vec3(0, 0, 10);
	glUniform3f(src_obj->LightID2, lightPos2.x, lightPos2.y, lightPos2.z);*/

	// Bind our texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, src_obj->Texture);
	// Set our "myTextureSampler" sampler to use Texture Unit 0
	glUniform1i(src_obj->TextureID, 0);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, src_obj->vertexbuffer);
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
	glBindBuffer(GL_ARRAY_BUFFER, src_obj->uvbuffer);
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
	glBindBuffer(GL_ARRAY_BUFFER, (unsigned)src_obj->normalbuffer);
	glVertexAttribPointer(
		2,                                // attribute
		3,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	// Draw the triangles !
	glDrawArrays(GL_TRIANGLES, 0, (unsigned)src_obj->vertices.size());

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}

void Renderer::Update(IUpdater* Iupdater)
{

}


void Renderer::addObject(RenderableObject* render_obj)
{
	Obj_List.push_back(render_obj);
}

void Renderer::renderObj()
{
	for (int i = 0; i < Obj_List.size(); i++)
	{
		render(Obj_List[i]);
	}
}

void Renderer::SetCameraPos(float x, float y, float z)
{
	CameraPos = glm::vec3(x, y, z);
}

void Renderer::renderglClear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::renderSwap()
{
	glfwSwapBuffers(GetWindow());
	glfwPollEvents();
}

glm::mat4 Renderer::getPosition(glm::mat4 ModelMatrix, RenderableObject* src_obj)
{
	float x, y, z;
	x = src_obj->PosX;
	y = src_obj->PosY;
	z = src_obj->PosZ;

	ModelMatrix = glm::translate(ModelMatrix, glm::vec3(x, y, z));
	return ModelMatrix;
}

void Renderer::Obj_Shutdown(RenderableObject* src_obj)
{
	src_obj->shutDown();
}

void Renderer::shutDown()
{
	glfwTerminate();
}

void Renderer::renderEnd()
{
	if (glfwGetKey(GetWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		exit(0);
	}
}
