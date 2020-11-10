#ifndef __RENDERER_H__
#define __RENDERER_H__

#include "FileManager.h"
#include "ICleanUp.h"
#include "IUpdater.h"
#include "ISetPos.h"

class RenderableObject;
class NonRenderableObject;

class Renderer : public ICleanUp, public IUpdater, public ISetPos
{
private:
	// Obj를 한번에 렌더하기 위한 리스트
	std::vector<RenderableObject*> Obj_List;
	std::vector<NonRenderableObject*> nonObj_List;

public:
	GLFWwindow* window;

public:
	static Renderer* instance()
	{
		static Renderer instance;

		return &instance;
	}

public:
	void render();
	void addObject(RenderableObject* render_obj);
	void addNonRenderObject(NonRenderableObject* render_obj);

	void init();
	void renderglClear();
	void renderSwap();
	void renderEnd();

	virtual void setPosition(float x, float y, float z) override;
	virtual void shutDown() override;
	virtual void Update() override;
};

#endif // !__RENDERER_H__