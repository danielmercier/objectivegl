#include <GL\glew.h>
#include <iostream>
#include <vector>


#pragma once
class VertexBuffer
{
public:
	VertexBuffer(GLenum target, GLsizei size,  GLenum usage);
	VertexBuffer(GLenum target, GLsizei size, const GLvoid *data, GLenum usage);
	~VertexBuffer();
	const void bind();
	const void unbind();
	const int getIndex();
	void subData(GLuint offset, GLsizei size, const GLvoid * data);
	void setData(GLsizei size, const GLvoid *data, GLenum usage);

private:
	GLuint _vbo;
	GLenum _target;
};