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
	void renderEnd();
	void Obj_Shutdown(RenderableObject* src_obj);
	void SetCameraPos(float x, float y, float z);

	virtual void Update(IUpdater *Iupdater) override;
	virtual void shutDown() override;

public:
	glm::mat4 MovePosition = glm::mat4(1.0);

	glm::vec3 CameraPos;

	// Initial position : on +Z 카메라 시작 위치
	glm::vec3 position = glm::vec3(0, 2, 10);
	// Initial horizontal angle : toward -Z
	float horizontalAngle = 3.14f;
	// Initial vertical angle : none
	float verticalAngle = 0.0f;
	// Initial Field of View
	float initialFoV = 45.0f;

	float MoveSpeed = 5.0f;
	float MouseSpeed = 0.005f;
};

#endif // !__RENDERER_H__