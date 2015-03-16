#pragma once
#include <GL\glew.h>
#include <vector>
#include "Renderer.h"
#include "MeshRender.h"

class GLRenderer :
	public Renderer
{
public:
	GLRenderer();
	~GLRenderer();
	virtual void render();
	virtual void beforeRendering(){ glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }
	virtual void afterRendering(){}
	void addMesh(MeshRender*);

private:
	std::vector<MeshRender*> _mesh;
};

