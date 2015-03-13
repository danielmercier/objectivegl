#pragma once
#include "GLRender.h"
#include "Program.h"
#include "Mesh.h"
#include "MeshDrawer.h"

class MyRender :
	public GLRender
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

