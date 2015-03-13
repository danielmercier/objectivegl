class Window;

#pragma once
class KeyHandler
{
public:
	virtual void keyPressed(Window *w, int key, int mods){}
	virtual void keyReleased(Window *w, int key, int mods){}
	virtual void keyRepeated(Window *w, int key, int mods){}
};