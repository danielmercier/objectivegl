#include <GL\glew.h>
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
#include <iostream>
#include <fstream>

#include "Window.h"
#include "MeshDrawer.h"
#include "Shader.h"
#include "Program.h"
#include "MyRender.h"
#include "GLRenderer.h"
#include "MeshRender.h"

using namespace std;

float vertices[] = { 1, 1, 1, -1, 1, 1, -1, -1, 1, 1, -1, 1,    // v0-v1-v2-v3 (front)
					 1, 1, 1, 1, -1, 1, 1, -1, -1, 1, 1, -1,    // v0-v3-v4-v5 (right)
					 1, 1, 1, 1, 1, -1, -1, 1, -1, -1, 1, 1,    // v0-v5-v6-v1 (top)
					-1, 1, 1, -1, 1, -1, -1, -1, -1, -1, -1, 1,    // v1-v6-v7-v2 (left)
					-1, -1, -1, 1, -1, -1, 1, -1, 1, -1, -1, 1,    // v7-v4-v3-v2 (bottom)
					 1, -1, -1, -1, -1, -1, -1, 1, -1, 1, 1, -1 };  // v4-v7-v6-v5 (back)

float normals[] = { 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1,    // v0-v1-v2-v3 (front)
					1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0,    // v0-v3-v4-v5 (right)
					0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0,    // v0-v5-v6-v1 (top)
					-1, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0,    // v1-v6-v7-v2 (left)
					0, -1, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0,    // v7-v4-v3-v2 (bottom)
					0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0, -1 };  // v4-v7-v6-v5 (back)

float *tex;
unsigned int *indices;

int main( void ){
	Window w(640, 480, "Test");

	int _size = 24;
	tex = new float[_size * 2];

	for (unsigned int i = 0; i<6; i++)
	{
		tex[i * 8] = 1;
		tex[i * 8 + 1] = 1;

		tex[i * 8 + 2] = 0;
		tex[i * 8 + 3] = 1;

		tex[i * 8 + 4] = 0;
		tex[i * 8 + 5] = 0;

		tex[i * 8 + 6] = 1;
		tex[i * 8 + 7] = 0;
	}


	int _indexSize = 36;
	indices = new unsigned int[_indexSize];

	int index = 0;
	for (unsigned int i = 0; i<_size; i += 4)
	{
		indices[index] = i; index++;
		indices[index] = i + 1; index++;
		indices[index] = i + 2; index++;

		indices[index] = i + 2; index++;
		indices[index] = i + 3; index++;
		indices[index] = i; index++;
	}

	MyRender render(640, 480);

	Mesh m;
	std::vector<float> v(vertices, vertices + _size * 3);
	std::vector<float> t(tex, tex + _size * 2);
	std::vector<unsigned int> ind(indices, indices + _indexSize);

	m.setVertices(v);
	m.setTexCoords(t);
	m.setIndices(ind);
	m.addData(std::vector<float>(normals, normals + _size * 3), 3);

	Program p;

	VertexShader vs("VS.glsl");
	std::cout << vs.getLog();
	FragmentShader fs("FS.glsl");
	std::cout << fs.getLog();

	p.attach(vs);
	p.attach(fs);
	p.link();

	p.linkParameter("view", &render.view);
	p.linkParameter("projection", &render.projection);

	MeshRender mr(new MeshDrawer(&m, GL_TRIANGLES, true), &p);
	mr.setModelName("model");
	render.addMesh(&mr);

	w.setRenderer(&render);

	return w.exec();
}