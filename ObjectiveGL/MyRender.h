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
	glm::mat4 model;

	void render();

private:
	int _width;
	int _height;
	MeshDrawer *_md;
	Program _p;
	std::vector<float> *_v;
};

