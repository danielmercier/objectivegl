#include "VertexArray.h"

GLuint VertexArray::_bound = 0;

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &_vao);
	_index = 0;
}

VertexArray::~VertexArray()
{
}

void VertexArray::attribBuffer(VertexBuffer &vb, GLint size, GLboolean normalized, GLsizei stride, const void* pointer){
	bind();
	vb.bind();
	glVertexAttribPointer(_index, size, GL_FLOAT, normalized, stride, pointer);
	glEnableVertexAttribArray(_index);
	_index++;
}

void VertexArray::attribBuffer(VertexBuffer &vb, GLint size, GLboolean normalized){
	attribBuffer(vb, size, normalized, 0, NULL);
}
void VertexArray::attribBuffer(VertexBuffer &vb, GLint size, GLsizei stride, const void* pointer){
	attribBuffer(vb, size, GL_FALSE, stride, pointer);
}
void VertexArray::attribBuffer(VertexBuffer &vb, GLint size){
	attribBuffer(vb, size, GL_FALSE, 0, NULL);
}

void VertexArray::bind(){
	glBindVertexArray(_vao);
}
void VertexArray::unbind(){
	_bound = 0;
	glBindVertexArray(0);
}