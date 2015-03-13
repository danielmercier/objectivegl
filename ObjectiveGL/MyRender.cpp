#include "MyRender.h"
#include "Window.h"
#include <glm.hpp>
#include <gtc\quaternion.hpp>
#include <gtc\matrix_transform.hpp>


MyRender::MyRender(int width, int height) : _width(width), _height(height)
{
}


MyRender::~MyRender()
{
}

void MyRender::beforeRendering(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glm::quat quat = glm::angleAxis((float)(Window::getTime()), normalize(glm::vec3(0, 1, 0)));
	view = glm::lookAt(quat * glm::vec3(0, 0, 4), glm::vec3(0, 0, 0), quat * glm::vec3(0, 1, 0));
	projection = glm::perspective(45.0f, (float)640 / (float)480, 0.2f, 10.0f);
}