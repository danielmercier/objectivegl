#include <GL\glew.h>

#include "Mesh.h"
#include "VertexArray.h"

#pragma once
class MeshDrawer
{
public:
	MeshDrawer(Mesh *mesh);
	~MeshDrawer();

	virtual void draw();

protected:
	VertexArray _va;

private:
	Mesh *_mesh;
	VertexBuffer *_ibo;

	void addOtherMeshElements();

	/*private methods*/
	void drawWithIndices();
	void drawWithoutIndices();

	void initBase();
	void addIndices();
};