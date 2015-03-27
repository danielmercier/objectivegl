#include "VertexBuffer.h"


VertexBuffer::VertexBuffer(GLenum target, GLsizei size, GLenum usage)
{
	_target = target;
	glGenBuffers(1, &_vbo);
	setData(size, NULL, usage);
}

VertexBuffer::VertexBuffer(GLenum target, GLsizei size, const void *data, GLenum usage)
{
	_target = target;
	glGenBuffers(1, &_vbo);
	setData(size, data, usage);
}

const void VertexBuffer::bind(){
	glBindBuffer(_target,_vbo);
}
const void VertexBuffer::unbind(){
	glBindBuffer(_target,0);
}
const int VertexBuffer::getIndex(){
	return _vbo;
}
void VertexBuffer::subData(GLuint offset, GLsizei size, const GLvoid* data){
	bind();
	glBufferSubData(_target, offset, size, data);
}

void VertexBuffer::setData(GLsizei size, const GLvoid *data, GLenum usage){
	bind();
	glBufferData(_target, size, data, usage);
}

VertexBuffer::~VertexBuffer()
{
}
