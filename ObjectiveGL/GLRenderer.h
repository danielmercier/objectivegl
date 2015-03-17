#pragma once
#include <GL\glew.h>
#include <vector>
#include "Renderer.h"
#include "MeshRender.h"

class GLRenderer :
	public Renderer
{
public:
	GLRenderer(){
		glewExperimental = GL_TRUE;
		glewInit();
	}

	~GLRenderer();
	virtual void render() = 0;
};

