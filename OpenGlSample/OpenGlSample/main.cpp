#define _CRT_SECURE_NO_WARNINGS

#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "lib-vc2017/glew32.lib")
#pragma comment(lib, "lib-vc2017/glfw3.lib")

#include "Object.h"
#include "FileManager.h"
#include "Renderer.h"
#include "RenderableObject.h"
#include "NonRenderableObject.h"
#include "Sphere.h"

int main()
{
	FileManager* filemgr = FileManager::instance();

	Renderer* renderer = Renderer::instance();
	renderer->init();

	Sphere* sphere = new Sphere(filemgr);
	renderer->addObject(sphere);
	sphere->SetPosition(-1.0f, 0.0f, 0.0f);

	RenderableObject* cube = new RenderableObject();
	renderer->addObject(cube);
	cube->SetPosition(1.0f, 0.0f, 0.0f);

	filemgr->loadOBJs(
		cube,
		"cube.obj",
		"goldskin.BMP",
		"20161614_vs.shader",
		"20161614_fs.shader"
	);


	NonRenderableObject* non_render_obj = new NonRenderableObject();

	while (true)
	{
		renderer->renderglClear();

		renderer->renderObj();
		renderer->Update(non_render_obj);

		renderer->renderSwap();

	}

	renderer->shutDown();

	delete cube;
	delete sphere;
	delete renderer;

	return 0;
}