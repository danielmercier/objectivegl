#include "MeshRender.h"


MeshRender::MeshRender(MeshDrawer *mesh, Program *p) : _mesh(mesh)
{
	_model = new glm::mat4(1.0f);
	setProgram(p);
}


MeshRender::~MeshRender()
{
}

void MeshRender::setProgram(Program *p){
	_p = p;
}

void MeshRender::setModel(const glm::mat4 &model){
	*_model = model;
}
void MeshRender::setModelName(const std::string &name){
	_uniform = name;
}

void MeshRender::render(){
	_p->use();
	beforeRendering();
	_p->setLinkedParameters();
	_p->setParameter(_uniform, *_model);
	_mesh->draw();
	afterRendering();
}