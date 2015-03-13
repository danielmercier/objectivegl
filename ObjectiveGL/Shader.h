#pragma once
#include <GL\glew.h>
#include <iostream>
#include <fstream>

class Shader
{
public:
	Shader(GLenum shaderType);
	~Shader();
	const GLuint getId();
	void load(const std::string &path);
	void compile();
	std::string getLog();

private:
	GLuint _id;

	static unsigned long getFileLength(std::ifstream &file);
};

class VertexShader :
	public Shader
{
public:
	VertexShader() : Shader(GL_VERTEX_SHADER){}
	VertexShader(const std::string &filename) : Shader(GL_VERTEX_SHADER){
		load(filename);
		compile();
	}
};

class FragmentShader :
	public Shader
{
public:
	FragmentShader() : Shader(GL_FRAGMENT_SHADER){}
	FragmentShader(const std::string &filename) : Shader(GL_FRAGMENT_SHADER){
		load(filename);
		compile();
	}
};