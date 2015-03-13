#include <GL\glew.h>
#include <glm.hpp>
#include <gtc\type_ptr.hpp>

#include "VertexBuffer.h"

#pragma once
class VertexArray
{
public:
	VertexArray();
	~VertexArray();
	void attribBuffer(VertexBuffer &vb, GLint size, GLboolean normalized, GLsizei stride, const void* pointer);
	void attribBuffer(VertexBuffer &vb, GLint size, GLboolean normalized);
	void attribBuffer(VertexBuffer &vb, GLint size, GLsizei stride, const void* pointer);
	void attribBuffer(VertexBuffer &vb, GLint size);

	/*Add all the buffer*/
	void bind();
	void unbind();

private:
	GLuint  _vao;
	int _index;

	/*Static fields*/
	/*track the bound vao*/
	static GLuint _bound;
};