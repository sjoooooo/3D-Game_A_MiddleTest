#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <vector>

#include "ICleanUp.h"
#include "IUpdater.h"

#include "include/GL/glew.h"
#include "include/GLFW/glfw3.h" 
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Object : public ICleanUp
{
	// 현재 기준으로 쓸일이 없기 때문에 주석 처리
public:
	virtual void shutDown() override;

public:
	//Object();
	virtual ~Object() {}
};

#endif