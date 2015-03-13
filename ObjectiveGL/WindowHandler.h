class Window;

#pragma once
class WindowHandler
{
public:
	virtual void windowClosed(Window *window){}
	virtual void windowResized(Window *window, int width, int height){}
	virtual void framebufferResized(Window *window, int width, int height){}
	virtual void windowMoved(Window *window, int xpos, int ypos){}
	virtual void windowReduced(Window *window, bool reduced){}
	virtual void windowFocused(Window *windo, bool focused){}
};