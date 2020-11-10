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
	Object* sphere = new Object();
	NonRenderableObject* non_render_obj = new NonRenderableObject();

	renderer->init();

	while (true)
	{
		renderer->renderglClear();

		// ���������� ���, ���Ž� ������������ ��
		if (TimeManager::GetInstance()->IsRenderTiming())
		{
			renderer->Update();
		}

		renderer->render();

		renderer->renderSwap();

		renderer->renderEnd();
	}

	renderer->shutDown();
	

	delete sphere;
	delete non_render_obj;

	return 0;
}