#include "GLRenderer.h"


GLRenderer::GLRenderer()
{
	glewExperimental = GL_TRUE;
	glewInit();
	glEnable(GL_DEPTH_TEST);
}


GLRenderer::~GLRenderer()
{
}

void GLRenderer::render(){
	beforeRendering();
	for each (MeshRender *m in _mesh)
	{
		m->render();
	}
	afterRendering();
}

void GLRenderer::addMesh(MeshRender* m){
	if (m){
		_mesh.push_back(m);
	}
}