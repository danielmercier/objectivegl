#pragma once
#include <vector>
#include "MeshDrawer.h"
#include "Program.h"

class MeshRender
{
public:
	MeshRender(MeshDrawer*, Program *p);
	~MeshRender();
	virtual void render();
	void setModel(const glm::mat4 &);
	void setModelName(const std::string &);
	void setProgram(Program *p);

	virtual void beforeRendering(){}
	virtual void afterRendering(){}

protected:
	glm::mat4 *_model;
	Program *_p;

private:
	MeshDrawer *_mesh;
	std::string _uniform;
};