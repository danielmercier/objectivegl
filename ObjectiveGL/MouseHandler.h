class Window;

#pragma once
class MouseHandler
{
public:
	virtual void mouseButtonPressed(Window *w, int button, int mods){}
	virtual void mouseButtonReleased(Window *w, int button, int mods){}
	virtual void mouseMoved(Window *w, double xpos, double ypos){}
	virtual void mouseEntered(Window *w, bool entered){}
	virtual void scrollHandler(Window *w, double xoffset, double yoffset){}
};