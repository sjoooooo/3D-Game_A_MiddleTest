#pragma once
#ifndef __RENDERER_H__
#define __RENDERER_H__

#include "ICleanUp.h"
#include "IUpdater.h"

struct GLFWwindow;
class Object;
class RenderableObject;

class Renderer : public ICleanUp, public IUpdater
{
private:
	GLFWwindow* window;

	// Obj를 한번에 렌더하기 위한 리스트
	std::vector<RenderableObject*> Obj_List;

public:
	GLFWwindow* GetWindow() const { return window; }

public:
	static Renderer* instance()
	{
		static Renderer instance;

		return &instance;
	}
public:
	glm::mat4 getPosition(glm::mat4 Model, RenderableObject* src_obj);

public:
	void render(RenderableObject* src_obj);
	void renderObj();
	void addObject(RenderableObject* render_obj);
	void init();

	void renderglClear();
	void renderSwap();
	void Obj_Shutdown(RenderableObject* src_obj);

	virtual void Update(IUpdater *Iupdater) override;
	virtual void shutDown() override;
};

#endif // !__RENDERER_H__