#include <string>
#include <iostream>
#include <stdio.h>
#include <GLFW\glfw3.h>

#include "Input.h"
#include "Renderer.h"

#pragma once
class Window
{
public:
	Window(int width, int height, const std::string &name, bool fullscreen = false);

	/*This construcor, construct a windowed full screen*/
	Window(const std::string &name);
	~Window();

	/*Main function to display window and render it*/
	int exec();

	/*Getter ans Setter for the window*/
	int getWidth();
	int getHeight();
	void setHeight(int height);
	void setWidth(int width);
	void setSize(int width, int height);

	void getFramebufferSize(int &width, int &height);

	void setTitle(const std::string &title);

	void setRenderer(Renderer *render);

	/*Inputs functions*/
	int getKeyState(int key);
	int getMouseButtonState(int button);
	void getCursorPos(double &xpos, double &ypos);

	void setMouseHandler(MouseHandler *h);
	void setKeyHandler(KeyHandler *h);
	void setDropHandler(DropHandler *h);
	void setWindowHandler(WindowHandler *h);

	void removeMouseHandler();
	void removeKeyHandler();
	void removeDropHandler();
	void removeWindowHandler();

	/*static public calls*/
	static double getTime();
	static void setTime(double time);

private:
	GLFWwindow *_window;
	Renderer *_render;
	Input *_in;
	/*Window width and height*/
	int _h; 
	int _w;

	/*Private method*/
	void initInputs();
	/*Static privated functions*/
	static void error_callback(int error, const char *description);

	static void mouse_button_callback(GLFWwindow *, int, int, int);
	static void cursor_pos_callback(GLFWwindow *, double, double);
	static void cursor_entered_callback(GLFWwindow *, int);
	static void scroll_callback(GLFWwindow *, double, double);
	static void key_callback(GLFWwindow *, int, int, int, int);
	static void drop_callback(GLFWwindow *, int, const char **);

	static void close_callback(GLFWwindow *window);
	static void resized_callback(GLFWwindow *window, int width, int height);
	static void framebuffer_resized_callback(GLFWwindow *window, int width, int height);
	static void move_callback(GLFWwindow *window, int xpos, int ypos);
	static void iconified_callback(GLFWwindow *window, int iconified);
	static void focus_callback(GLFWwindow *windo, int focused);
};
