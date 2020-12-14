#pragma once
#include "glm/gtc/matrix_transform.hpp"
#include "glm/glm.hpp"
#include "include/GL/glew.h"		
#include "include/GLFW/glfw3.h" 

#include "ICleanUp.h"
#include "IUpdater.h"
#include "IInit.h"
#include "IRenderer.h"
#include "ISetPos.h"

class ObjectManager : public ICleanUp, public IUpdater, public IInit, public IRenderer, public ISetPos
{
public:

	virtual ~ObjectManager() {};
};