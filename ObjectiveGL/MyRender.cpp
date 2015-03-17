#include "MyRender.h"
#include "Window.h"
#include <glm.hpp>
#include <gtc\quaternion.hpp>
#include <gtc\matrix_transform.hpp>

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

MyRender::MyRender(int width, int height) : _width(width), _height(height)
{
	glEnable(GL_DEPTH_TEST);

	VertexShader vs("VS.glsl");
	std::cout << vs.getLog();
	FragmentShader fs("FS.glsl");
	std::cout << fs.getLog();

	_p.attach(vs);
	_p.attach(fs);
	_p.link();

	_p.linkParameter("view", &view);
	_p.linkParameter("projection", &projection);
	_p.linkParameter("model", &model);

	int _size = 24;
	float *tex = new float[_size * 2];

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
	unsigned int *indices = new unsigned int[_indexSize];

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

	Mesh *m = new Mesh;
	std::vector<float> v(vertices, vertices + _size * 3);
	std::vector<float> t(tex, tex + _size * 2);
	std::vector<unsigned int> ind(indices, indices + _indexSize);

	m->setVertices(v);
	m->setTexCoords(t);
	m->setIndices(ind);
	m->addData(std::vector<float>(normals, normals + _size * 3), 3);

	_md = new MeshDrawer(m, GL_TRIANGLES, true);
}


MyRender::~MyRender()
{
}

void MyRender::render(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glm::quat quat = glm::angleAxis((float)(Window::getTime()), normalize(glm::vec3(0, 1, 0)));
	view = glm::lookAt(quat * glm::vec3(0, 0, 4), glm::vec3(0, 0, 0), quat * glm::vec3(0, 1, 0));
	projection = glm::perspective(45.0f, (float)640 / (float)480, 0.2f, 10.0f);

	_md->draw(_p);
}