#include "BezierRenderer.h"
#include "Window.h"

BezierRenderer::BezierRenderer(int precision)
{
	_line.resize(precision * 3);
	_mesh.setDynamicalVertices(&_line);
	_md = new MeshDrawer(&_mesh, GL_LINE_STRIP);
	_p = new Program("VS.glsl", "FS.glsl");
}


BezierRenderer::~BezierRenderer()
{
}

void BezierRenderer::mouseButtonPressed(Window *w, int button, int mods){
	double x;
	double y;

	w->getCursorPos(x, y);

	x /= 320;
	y /= 240;

	x -= 1;
	y = 1 - y;

	b.addPoint(x, y);
	b.print();
}

void BezierRenderer::render(){
	glClear(GL_COLOR_BUFFER_BIT);
	for (int i = 0; i < (_line.size() / 3); i++){
		float *p = b.calculate((float)i / ((float)_line.size() - 1));
		_line[i * 3] = p[0];
		_line[i * 3 + 1] = p[1];
		_line[i * 3 + 2] = 0;
	}	

	_md->draw(*_p);
}