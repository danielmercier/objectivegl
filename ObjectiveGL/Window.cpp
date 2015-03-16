#include "Window.h"
#include "MouseHandler.h"

void Window::error_callback(int error, const char *description){
	std::cerr << description << std::endl;
}

Window::Window(int width, int height, const std::string &name, bool fullscreen) : _h(height), _w(width)
{
	glfwSetErrorCallback(Window::error_callback);

	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}

	/*Fullscreen or not*/
	GLFWmonitor *monitor = (fullscreen) ? glfwGetPrimaryMonitor() : NULL;
	_window = glfwCreateWindow(width, height, name.c_str(), monitor, NULL);
	if (!_window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	
	/* Make the window's context current */
	glfwMakeContextCurrent(_window);
	initInputs();
	_render = new Renderer();
}

Window::Window(const std::string &name){
	glfwSetErrorCallback(Window::error_callback);

	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}

	GLFWmonitor *monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);

	glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

	_w = mode->width;
	_h = mode->height;
	_window = glfwCreateWindow(mode->width, mode->height, name.c_str(), monitor, NULL);

	if (!_window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(_window);

	initInputs();

	_render = new Renderer();
}


Window::~Window()
{
	if (_in)
		delete(_in);

	if (_window){
		glfwDestroyWindow(_window);
	}

	glfwTerminate();
}

int Window::exec(){
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(_window))
	{
		/* Render here */
		_render->render();
		/* Swap front and back buffers */
		glfwSwapBuffers(_window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	return EXIT_SUCCESS;
}

int Window::getWidth(){
	return _w;
}

int Window::getHeight(){
	return _h;
}

void Window::setHeight(int height){
	setSize(_w, height);
}
void Window::setWidth(int width){
	setSize(width, _h);
}

void Window::setSize(int width, int height){
	glfwSetWindowSize(_window, width, height);
}

void Window::getFramebufferSize(int &width, int &height){
	glfwGetFramebufferSize(_window, &width, &height);
}

void Window::setTitle(const std::string &title){
	glfwSetWindowTitle(_window, title.c_str());
}

void Window::setRenderer(Renderer *render){
	this->_render = render;
}

int Window::getKeyState(int key){
	return glfwGetKey(_window, key);
}
int Window::getMouseButtonState(int button){
	return glfwGetMouseButton(_window, button);
}
void Window::getCursorPos(double &xpos, double &ypos){
	glfwGetCursorPos(_window, &xpos, &ypos);
}

void Window::setMouseHandler(MouseHandler *h){
	if (h){
		_in->mh = h;
		glfwSetMouseButtonCallback(_window, Window::mouse_button_callback);
		glfwSetCursorPosCallback(_window, Window::cursor_pos_callback);
		glfwSetCursorEnterCallback(_window, Window::cursor_entered_callback);
		glfwSetScrollCallback(_window, Window::scroll_callback);
	}
	else{
		removeMouseHandler();
	}
}
void Window::setKeyHandler(KeyHandler *h){
	if (h){
		_in->kh = h;
		glfwSetKeyCallback(_window, Window::key_callback);
	}
	else
	{
		removeKeyHandler();
	}
}
void Window::setDropHandler(DropHandler *h){
	if (h){
		_in->dh = h;
		glfwSetDropCallback(_window, Window::drop_callback);
	}
	else{
		removeDropHandler();
	}
}
void Window::setWindowHandler(WindowHandler *h){
	if (h){
		_in->wh = h;
		glfwSetWindowCloseCallback(_window, Window::close_callback);
		glfwSetFramebufferSizeCallback(_window, Window::framebuffer_resized_callback);
		glfwSetWindowPosCallback(_window, Window::move_callback);
		glfwSetWindowIconifyCallback(_window, Window::iconified_callback);
		glfwSetWindowFocusCallback(_window, Window::focus_callback);
	}
	else{
		removeDropHandler();
	}
}

void Window::removeMouseHandler(){
	_in->mh = NULL;
	glfwSetMouseButtonCallback(_window, NULL);
	glfwSetCursorPosCallback(_window, NULL);
	glfwSetCursorEnterCallback(_window, NULL);
	glfwSetScrollCallback(_window, NULL);
}
void Window::removeKeyHandler(){
	_in->kh = NULL;
	glfwSetKeyCallback(_window, NULL);
}
void Window::removeDropHandler(){
	_in->dh = NULL;
	glfwSetDropCallback(_window, NULL);
}
void Window::removeWindowHandler(){
	_in->wh = NULL;
	glfwSetWindowCloseCallback(_window, NULL);
	glfwSetFramebufferSizeCallback(_window, NULL);
	glfwSetWindowPosCallback(_window, NULL);
	glfwSetWindowIconifyCallback(_window, NULL);
	glfwSetWindowFocusCallback(_window, NULL);
}

double Window::getTime(){
	return glfwGetTime();
}
void Window::setTime(double time){
	glfwSetTime(time);
}

void Window::mouse_button_callback(GLFWwindow *w, int button, int action, int mods){
	Input *i = (Input*)glfwGetWindowUserPointer(w);
	
	if (action == GLFW_PRESS){
		i->mh->mouseButtonPressed(i->w, button, mods);
	}
	else{
		i->mh->mouseButtonReleased(i->w, button, mods);
	}
}
void Window::cursor_pos_callback(GLFWwindow *w, double xpos, double ypos){
	Input *i = (Input*)glfwGetWindowUserPointer(w);
	i->mh->mouseMoved(i->w, xpos, ypos);
}
void Window::cursor_entered_callback(GLFWwindow *w, int entered){
	Input *i = (Input*)glfwGetWindowUserPointer(w);
	i->mh->mouseEntered(i->w, entered);
}
void Window::scroll_callback(GLFWwindow *w, double xoffset, double yoffset){
	Input *i = (Input*)glfwGetWindowUserPointer(w);
	i->mh->scrollHandler(i->w, xoffset, yoffset);
}
void Window::key_callback(GLFWwindow *w, int key, int scancode, int action, int mods){
	Input *i = (Input*)glfwGetWindowUserPointer(w);
	switch (action){
	case GLFW_PRESS:
		i->kh->keyPressed(i->w, key, mods);
		break;
	case GLFW_RELEASE:
		i->kh->keyReleased(i->w, key, mods);
		break;
	case GLFW_REPEAT:
		i->kh->keyRepeated(i->w, key, mods);
		break;
	}
}
void Window::drop_callback(GLFWwindow *w, int count, const char **names){
	Input *i = (Input*)glfwGetWindowUserPointer(w);
	std::vector<std::string> n(names, names + count);
	
	i->dh->dropped(i->w, n);
}

void Window::close_callback(GLFWwindow *w){
	Input *i = (Input*)glfwGetWindowUserPointer(w);
	i->wh->windowClosed(i->w);
}
void Window::resized_callback(GLFWwindow *w, int width, int height){
	Input *i = (Input*)glfwGetWindowUserPointer(w);
	i->w->_w = width;
	i->w->_h = height;

	if (i->wh)
		i->wh->windowResized(i->w, width, height);
	
}
void Window::framebuffer_resized_callback(GLFWwindow *w, int width, int height){
	Input *i = (Input*)glfwGetWindowUserPointer(w);
	i->wh->framebufferResized(i->w, width, height);
}
void Window::move_callback(GLFWwindow *w, int xpos, int ypos){
	Input *i = (Input*)glfwGetWindowUserPointer(w);
	i->wh->windowMoved(i->w, xpos, ypos);
}
void Window::iconified_callback(GLFWwindow *w, int iconified){
	Input *i = (Input*)glfwGetWindowUserPointer(w);
	i->wh->windowReduced(i->w, iconified);
}
void Window::focus_callback(GLFWwindow *w, int focused){
	Input *i = (Input*)glfwGetWindowUserPointer(w);
	i->wh->windowFocused(i->w, focused);
}
void Window::initInputs(){
	/*Inputs*/
	glfwSetWindowSizeCallback(_window, resized_callback);

	_in = new Input;
	_in->w = this;
	_in->dh = NULL;
	_in->kh = NULL;
	_in->wh = NULL;
	_in->mh = NULL;
	glfwSetWindowUserPointer(_window, _in);
}