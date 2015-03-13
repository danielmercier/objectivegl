#include "VertexBuffer.h"


VertexBuffer::VertexBuffer(GLenum target, GLsizei size, GLenum usage)
{
	_target = target;
	glGenBuffers(1, &_vbo);
	bind();
	glBufferData(target, size, NULL, usage);
}

VertexBuffer::VertexBuffer(GLenum target, GLsizei size, const void *data, GLenum usage)
{
	_target = target;
	glGenBuffers(1, &_vbo);
	bind();
	glBufferData(target, size, data, usage);
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

VertexBuffer::~VertexBuffer()
{
}
