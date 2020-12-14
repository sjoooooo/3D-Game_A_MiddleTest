#include "KeyManager.h"
#include "Renderer.h"

KeyManager* KeyManager::instance = 0;
Renderer* renderer = Renderer::instance();

void KeyManager::UseKeyBoard()
{
	// glfwGetTime is called only once, the first time this function is called
	static double lastTime = glfwGetTime();

	// Compute time difference between current and last frame
	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);

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

	//// Move forward
	//if (glfwGetKey(renderer->window, GLFW_KEY_W) == GLFW_PRESS) {
	//	position += direction * deltaTime * MoveSpeed;
	//}
	//// Move backward
	//if (glfwGetKey(renderer->window, GLFW_KEY_S) == GLFW_PRESS) {
	//	position -= direction * deltaTime * MoveSpeed;
	//}
	// Strafe left
	if (glfwGetKey(renderer->window, GLFW_KEY_A) == GLFW_PRESS) {
		position -= right * deltaTime * MoveSpeed;
	}
	// Strafe right
	if (glfwGetKey(renderer->window, GLFW_KEY_D) == GLFW_PRESS) {
		position += right * deltaTime * MoveSpeed;
	}

	float FoV = initialFoV;

	// Compute the MVP matrix from keyboard and mouse input // 45.0f
	ProjectionMatrix = glm::perspective(glm::radians(FoV), 4.0f / 3.0f, 0.1f, 100.0f);
	// Camera matrix
	//glm::mat4 ViewMatrix = glm::lookAt(
	//	glm::vec3(0, 5, 7), // Camera is at (4,3,3), in World Space
	//	glm::vec3(0, 0, 0), // and looks at the origin
	//	glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
	ViewMatrix = glm::lookAt(
		position,           // Camera is here
		position + direction, // and looks here : at the same position, plus "direction"
		up                  // Head is up (set to 0,-1,0 to look upside-down)
	);

	// For the next frame, the "last time" will be "now"
	lastTime = currentTime;
}

void KeyManager::UseMouse()
{
	// Get mouse position
	double xpos, ypos;
	glfwGetCursorPos(renderer->window, &xpos, &ypos);

	// 마우스 커서 숨기기
	glfwSetInputMode(renderer->window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	// Reset mouse position for next frame
	glfwSetCursorPos(renderer->window, 1024 / 2, 768 / 2);

	// Compute new orientation
	horizontalAngle += MouseSpeed * float(1024 / 2 - xpos);
	verticalAngle += MouseSpeed * float(768 / 2 - ypos);
}