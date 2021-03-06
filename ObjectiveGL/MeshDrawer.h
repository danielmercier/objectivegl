#include <GL\glew.h>

#include "Mesh.hpp"
#include "VertexArray.h"
#include "Program.h"

#pragma once
class MeshDrawer
{
public:
	MeshDrawer(Mesh *mesh, GLenum drawMod, bool useIndices = false);
	~MeshDrawer();

	virtual void draw();
	virtual void draw(Program &);

private:
	Mesh *_mesh;
	bool _useIndices;
	GLenum _drawMod;

	void drawWithIndices();
	void drawWithoutIndices();
};