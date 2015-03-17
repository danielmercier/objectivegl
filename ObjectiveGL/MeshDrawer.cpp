#include "MeshDrawer.h"
#include "VertexBuffer.h"

MeshDrawer::MeshDrawer(Mesh *mesh, GLenum drawMod, bool useIndices) : _mesh(mesh), _drawMod(drawMod), _useIndices(useIndices)
{
}

MeshDrawer::~MeshDrawer(){
}

void MeshDrawer::draw(){
	if (_useIndices){
		drawWithIndices();
	}
	else{
		drawWithoutIndices();
	}
}

void MeshDrawer::draw(Program &p){
	p.setLinkedParameters();
	draw();
}

void MeshDrawer::drawWithIndices(){
	/*Bind the correct vao and the ibo*/
	_mesh->getVertexArray().bind();
	_mesh->getIndices().bind();
	glDrawElements(_drawMod, _mesh->getSize() , GL_UNSIGNED_INT, 0);

	/*Unbind the vao*/
	_mesh->getVertexArray().unbind();
}
void MeshDrawer::drawWithoutIndices(){
	/*Bind the correct vao*/
	_mesh->getVertexArray().bind();

	glDrawArrays(_drawMod, 0, _mesh->getSize());

	/*Unbind the vao*/
	_mesh->getVertexArray().unbind();
}
