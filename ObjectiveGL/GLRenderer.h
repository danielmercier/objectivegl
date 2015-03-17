#pragma once
#include <GL\glew.h>
#include <vector>
#include "Renderer.h"

class GLRenderer :
	public Renderer
{
public:
	GLRenderer(){
		glewExperimental = GL_TRUE;
		glewInit();
	}

	virtual void render() = 0;
};

