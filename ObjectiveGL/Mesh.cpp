#include "Mesh.h"
#include <iostream>

/*Empty Constructor*/
Mesh::Mesh(bool useIndices){
	_useIndices = useIndices;
}

void Mesh::addData(float *data, int size, int nb, bool normalized){
	Mesh::dataFVAO d;
	d.data = data;
	d.normalized = normalized;
	d.size = size;
	d.nb = nb;
	_data.push_back(d);
}

/*Setters*/
void Mesh::setDrawMod(int drawMod){
	_drawMod = drawMod;
}
void Mesh::setVertices(std::vector<vertex> vertices){
	_vertices = vertices;
}
void Mesh::setIndices(std::vector<unsigned int> indices){
	_indices = indices;
}

/*Getters*/
int Mesh::getDrawMod(){
	return _drawMod;
}
std::vector<Mesh::vertex> Mesh::getVertices(){
	return _vertices;
}
bool Mesh::useIndices(){
	return _useIndices;
}
std::vector<unsigned int> Mesh::getIndices(){
	return _indices;
}