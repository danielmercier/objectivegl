#include "GLRender.h"


GLRender::GLRender()
{
	glewExperimental = GL_TRUE;
	glewInit();
	glEnable(GL_DEPTH_TEST);
}


GLRender::~GLRender()
{
}

void GLRender::render(){
	beforeRendering();
	for each (MeshRender *m in _mesh)
	{
		m->render();
	}
	afterRendering();
}

void GLRender::addMesh(MeshRender* m){
	if (m){
		_mesh.push_back(m);
	}
}