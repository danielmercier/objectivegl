#include "Mesh.hpp"
#include <iostream>

/*Empty Constructor*/
Mesh::Mesh(){
	_size = -1;
}

void Mesh::setVertices(std::vector<float> vertices){
	VertexBuffer vbo(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
	_vao.attribBuffer(vbo, 3);

	if (_size == -1)
		_size = vertices.size();
}
void Mesh::setTexCoords(std::vector<float> texCoords){
	VertexBuffer vbo(GL_ARRAY_BUFFER, texCoords.size() * sizeof(float), texCoords.data(), GL_STATIC_DRAW);
	_vao.attribBuffer(vbo, 2);
}

void Mesh::setIndices(std::vector<unsigned int> indices){
	_ibo = new VertexBuffer(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
	_size = indices.size();
}