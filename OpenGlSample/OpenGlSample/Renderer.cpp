#include <stdio.h>

#include "Object.h"
#include "Renderer.h"
#include "Sphere.h"
#include "RenderableObject.h"
#include "NonRenderableObject.h"

#include "include/GL/glew.h"
#include "include/GLFW/glfw3.h" 
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


void Renderer::addObject(RenderableObject* render_obj)
{
	Obj_List.push_back(render_obj);
}

void Renderer::addNonRenderObject(NonRenderableObject* render_obj)
{
	nonObj_List.push_back(render_obj);
}

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
	//glfwPollEvents();
	//glfwSetCursorPos(window, 1024 / 2, 768 / 2);

	// Dark blue background
	glClearColor(0.2f, 0.2f, 0.2f, 0.0f);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	// Cull triangles which normal is not towards the camera
	//glEnable(GL_CULL_FACE);

	for (std::vector<RenderableObject*>::iterator iter = Obj_List.begin(); iter != Obj_List.end(); iter++)
	{
		(*iter)->init();
	}

	for (std::vector<NonRenderableObject*>::iterator iter = nonObj_List.begin(); iter != nonObj_List.end(); iter++)
	{
		(*iter)->init();
	}
}

void Renderer::render()
{
	for (std::vector<RenderableObject*>::iterator iter = Obj_List.begin(); iter != Obj_List.end(); iter++)
	{
		(*iter)->render();
	}

	for (std::vector<NonRenderableObject*>::iterator iter = nonObj_List.begin(); iter != nonObj_List.end(); iter++)
	{
		(*iter)->render();
	}
}

void Renderer::setPosition(float x, float y, float z)
{

}

void Renderer::Update()
{
	for (std::vector<RenderableObject*>::iterator iter = Obj_List.begin(); iter != Obj_List.end(); iter++)
	{
		(*iter)->Update();
	}

	for (std::vector<NonRenderableObject*>::iterator iter = nonObj_List.begin(); iter != nonObj_List.end(); iter++)
	{
		(*iter)->Update();
	}
}

void Renderer::shutDown()
{
	for (std::vector<RenderableObject*>::iterator iter = Obj_List.begin(); iter != Obj_List.end(); iter++)
	{
		(*iter)->shutDown();
	}

	for (std::vector<NonRenderableObject*>::iterator iter = nonObj_List.begin(); iter != nonObj_List.end(); iter++)
	{
		(*iter)->shutDown();
	}

	glfwTerminate();
}

void Renderer::renderglClear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::renderSwap()
{
	glfwSwapBuffers(window);
	glfwPollEvents();
}

void Renderer::renderEnd()
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		exit(0);
	}
}
