#include "MeshDrawer.h"
#include "VertexBuffer.h"

MeshDrawer::MeshDrawer(Mesh *mesh) : _mesh(mesh), _ibo(NULL)
{
	initBase();
	if (_mesh->useIndices()){
		addIndices();
	}
	addOtherMeshElements();
}

MeshDrawer::~MeshDrawer(){
	delete(_ibo);
}

void MeshDrawer::draw(){
	if (_mesh->useIndices()){
		drawWithIndices();
	}
	else{
		drawWithoutIndices();
	}
}

void MeshDrawer::addIndices(){
	GLuint size = _mesh->getIndices().size() * sizeof(unsigned int);

	_ibo = new VertexBuffer(GL_ELEMENT_ARRAY_BUFFER, size, _mesh->getIndices().data(), GL_STATIC_DRAW);
}

void MeshDrawer::initBase(){
	std::vector<Mesh::vertex> vertices = _mesh->getVertices();
	unsigned int size = sizeof(Mesh::vertex)* vertices.size();

	VertexBuffer vbo(GL_ARRAY_BUFFER, size, vertices.data(), GL_STATIC_DRAW);

	//The number of bytes beetween two first elements of specific data
	//This number is the size of structure vertex
	unsigned int stride = sizeof(Mesh::vertex);
	_va.attribBuffer(vbo, 3, stride, (GLuint*)NULL);

	_va.attribBuffer(vbo, 2, stride, (GLuint*)(3 * sizeof(float)));
}

void MeshDrawer::drawWithIndices(){
	/*Bind the correct vao and the ibo*/
	_va.bind();
	_ibo->bind();
	glDrawElements(_mesh->getDrawMod(), _mesh->getIndices().size() , GL_UNSIGNED_INT, 0);

	/*Unbind the vao*/
	_va.unbind();
}
void MeshDrawer::drawWithoutIndices(){
	/*Bind the correct vao*/
	_va.bind();
	glDrawArrays(_mesh->getDrawMod(), 0, _mesh->getVertices().size());

	/*Unbind the vao*/
	_va.unbind();
}

void MeshDrawer::addOtherMeshElements(){
	for each (Mesh::dataFVAO d in _mesh->_data)
	{
		VertexBuffer vb(GL_ARRAY_BUFFER, d.size * sizeof(float), d.data, GL_STATIC_DRAW);
		_va.attribBuffer(vb, d.nb, d.normalized);
	}
}
