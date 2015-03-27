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
#include "BezierRenderer.h"

using namespace std;

int main( void ){
	Window w(640, 480, "Test");
	BezierRenderer render(100);
	
	w.setMouseHandler(&render);
	w.setRenderer(&render);

	return w.exec();
}