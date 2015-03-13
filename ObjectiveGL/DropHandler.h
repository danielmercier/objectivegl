#include <vector>

class Window;

#pragma once
class DropHandler
{
public:
	virtual void dropped(Window *w, std::vector<std::string> names){}
};