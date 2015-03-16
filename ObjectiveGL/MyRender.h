#pragma once
#include "GLRenderer.h"
#include "Program.h"
#include "Mesh.hpp"
#include "MeshDrawer.h"

class MyRender :
	public GLRenderer
{
public:
	MyRender(int width, int height);
	~MyRender();
	void beforeRendering();
	glm::mat4 projection;
	glm::mat4 view;

private:
	int _width;
	int _height;
};

