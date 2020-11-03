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
#include "LoadBackground.h"
#include "House.h"
#include "TimeManager.h"

int main()
{
	FileManager* filemgr = FileManager::instance();

	Renderer* renderer = Renderer::instance();
	renderer->init();

	Sphere* contatiner1 = new Sphere(filemgr);
	renderer->addObject(contatiner1);
	contatiner1->SetPosition(-10.0f, 0.0f, 0.0f);

	Sphere* contatiner2 = new Sphere(filemgr);
	renderer->addObject(contatiner2);
	contatiner2->SetPosition(-10.0f, 0.0f, 10.0f);

	Sphere* contatiner3 = new Sphere(filemgr);
	renderer->addObject(contatiner3);
	contatiner3->SetPosition(-10.0f, 0.0f, 20.0f);

	LoadBackground* background = new LoadBackground(filemgr);
	renderer->addObject(background);
	background->SetPosition(0.0f, 0.0f, 0.0f);

	/*House* house = new House(filemgr);
	renderer->addObject(house);
	house->SetPosition(30.0f, 0.5f, 10.0f);*/

	RenderableObject* woodtower = new RenderableObject();
	renderer->addObject(woodtower);
	woodtower->SetPosition(10.0f, -0.5f, -10.0f);

	RenderableObject* ground = new RenderableObject();
	renderer->addObject(ground);
	ground->SetPosition(0.0f, 0.0f, 0.0f);


	filemgr->loadOBJs(
		ground,
		"ground.obj",
		"snow.BMP",
		"20161614_vs.shader",
		"20161614_fs.shader"
	);

	filemgr->loadOBJs(
		woodtower,
		"woodtower.obj",
		"silverskin.BMP",
		"20161614_vs.shader",
		"20161614_fs.shader"
	);


	NonRenderableObject* non_render_obj = new NonRenderableObject();

	while (true)
	{
		renderer->renderglClear();

		// 고정프레임 사용, 제거시 가변프레임이 됨
		if (TimeManager::GetInstance()->IsRenderTiming())
		{
			renderer->Update(non_render_obj);
		}

		renderer->renderObj();

		renderer->renderSwap();

		renderer->renderEnd();
	}

	renderer->shutDown();
	

	delete background;
	delete ground;
	delete contatiner1;
	delete contatiner2;
	delete contatiner3;
	delete renderer;

	return 0;
}