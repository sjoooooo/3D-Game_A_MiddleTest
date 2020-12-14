#define _CRT_SECURE_NO_WARNINGS

#pragma comment(lib,"winmm.lib") 
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
#include "TimeManager.h"
#include "CompositeObject.h"

#include "../BackGround.h"
#include "../Snow.h"
#include "../Snowman.h"
#include "../UI.h"

bool CheckCollision(CompositeObject* one, CompositeObject* two)
{
	bool collisionX = one->position.x + 1.0 >= (two->position.x) / 2 && (two->position.x) / 2 + 1 >= one->position.x;
	bool collisionY = one->position.y + 1.0 >= (two->position.y) / 2 &&	(two->position.y) / 2 + 1 >= one->position.y;
	bool collisionZ = one->position.z + 1.0 >= (two->position.z) / 2 &&	(two->position.z) / 2 + 1 >= one->position.z;
	return collisionX && collisionY && collisionZ;
}

int main()
{
	PlaySound(TEXT("WhiteChristmas.wav"), NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);

	Renderer* renderer = Renderer::instance();
	Snowman* snowman = new Snowman();
	Background* background = new Background();
	UI* ui = new UI();

	std::vector<Snow*>* snow = new std::vector<Snow*>();

	for (int i = 0; i < 30; i++)
	{
		snow->push_back(new Snow());
	}


	NonRenderableObject* non_render_obj = new NonRenderableObject();

	renderer->init();

	snowman->setScale(0.3f, 0.3f, 0.3f);
	background->setScale(5.0f, 5.0f, 0.1f);

	for (
		std::vector<Snow*>::const_iterator it = snow->begin();
		it != snow->end();
		++it
		)
	{
		(*it)->setScale(0.1f, 0.1f, 0.1f);
	}

	while (true)
	{
		renderer->renderglClear();

		// 고정프레임 사용, 제거시 가변프레임이 됨
		if (TimeManager::GetInstance()->IsRenderTiming())
		{
			renderer->Update();
		}

		renderer->render();

		for (
			std::vector<Snow*>::const_iterator it = snow->begin();
			it != snow->end();
			++it
			)
		{
			if (CheckCollision(snowman, (*it)))
			{
				snowman->setPosition(0.0f, 20.0f, 0.0f);
				snowman->setLife(false);
				ui->setDie(false);
			}
		}

		if (ui->getDie() && snowman->getLife() == false)
		{
			snowman->init();

			for (
				std::vector<Snow*>::const_iterator it = snow->begin();
				it != snow->end();
				++it
				)
			{
				(*it)->init();
			}

		}

		renderer->renderSwap();

		renderer->renderEnd();
	}

	renderer->shutDown();

	for (
		std::vector<Snow*>::const_iterator it = snow->begin();
		it != snow->end();
		++it
		)
	{
		delete (*it);
	}

	delete snow;
	delete snowman;
	delete background;
	delete ui;
	delete non_render_obj;

	return 0;
}

