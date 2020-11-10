#pragma once
#include "FileManager.h"
#include <vector>

class KeyManager
{
private:
	static KeyManager* instance;

public:

	static KeyManager* GetInstance()
	{
		if (instance == 0)
		{
			instance = new KeyManager();
		}

		return instance;
	};

public:
	void UseKeyBoard();

public:


	glm::mat4 ViewMatrix;
	glm::mat4 ProjectionMatrix;

	glm::mat4 getViewMatrix() {
		return ViewMatrix;
	}
	glm::mat4 getProjectionMatrix() {
		return ProjectionMatrix;
	}

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