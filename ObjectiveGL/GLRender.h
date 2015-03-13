#pragma once
#include <GL\glew.h>
#include <vector>
#include "Render.h"
#include "MeshRender.h"

class GLRender :
	public Render
{
public:
	GLRender();
	~GLRender();
	virtual void render();
	virtual void beforeRendering(){ glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }
	virtual void afterRendering(){}
	void addMesh(MeshRender*);

private:
	std::vector<MeshRender*> _mesh;
};

