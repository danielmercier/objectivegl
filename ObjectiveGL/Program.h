#pragma once
#include <GL\glew.h>
#include <glm.hpp>
#include <gtc\type_ptr.hpp>
#include <iostream>
#include <map>
#include <vector>
#include "Shader.h"

class Program
{
public:
	Program();
	Program(const std::string &vertex, const std::string &fragment);
	~Program();
	std::string getLog();
	void use();
	void attach(Shader &sh);
	void detach(Shader &sh);
	void link();

	void setParameter(const std::string &, int);
	void setParameter(const std::string &, float);
	void setParameter(const std::string &, const glm::vec2 &);
	void setParameter(const std::string &, const glm::vec3 &);
	void setParameter(const std::string &, const glm::vec4 &);
	void setParameter(const std::string &, const glm::mat4 &);

	void linkParameter(const std::string &, const int *);
	void linkParameter(const std::string &, const float *);
	void linkParameter(const std::string &, const glm::vec2 *);
	void linkParameter(const std::string &, const glm::vec3 *);
	void linkParameter(const std::string &, const glm::vec4 *);
	void linkParameter(const std::string &, const glm::mat4 *);

	void setLinkedParameters();

	static void stopUsing();

	int getId(){
		return _id;
	}
private:
	GLuint _id;
	std::map < std::string, int > _map;
	typedef enum type{INT,FLOAT,VEC2,VEC3,VEC4,MAT4};
	struct triplet{
		std::string s;
		type t;
		void* v;
	};

	std::vector<triplet> _parameters;

	int location(const std::string &);

	static GLuint usedProgram;
};

