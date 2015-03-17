#include "Program.h"
#include "Shader.h"

GLuint Program::usedProgram = 0;

Program::Program()
{
	_id = glCreateProgram();
}

Program::Program(const std::string vertex, const std::string &fragment){
	Program();
	VertexShader vert(vertex);
	FragmentShader frag(fragment);
	attach(vert);
	attach(frag);
	link();
}

Program::~Program()
{
	stopUsing();
	glDeleteProgram(_id);
}

void Program::attach(Shader &sh){
	glAttachShader(_id, sh.getId());
}

void Program::detach(Shader &sh){
	glDetachShader(_id, sh.getId());
}

void Program::use(){
	if (usedProgram != _id){
		glUseProgram(_id);
		usedProgram = _id;
	}
}

void Program::link(){
	glLinkProgram(_id);
}

std::string Program::getLog(){
	int infologLength = 0;
	int maxLength;

	glGetProgramiv(_id, GL_INFO_LOG_LENGTH, &maxLength);

	char *infoLog = new char[maxLength];

	glGetProgramInfoLog(_id, maxLength, &infologLength, infoLog);

	std::string log(infoLog);

	delete[] infoLog;

	return log;
}

void Program::stopUsing(){
	if (usedProgram != 0){
		glUseProgram(0);
		usedProgram = 0;
	}
}

void Program::setParameter(const std::string & uniform, int value){
	use();
	int loc = location(uniform);
	glUniform1i(loc, value);
}

void Program::setParameter(const std::string & uniform, float value){
	use();
	int loc = location(uniform);
	glUniform1f(loc, value);
}

void Program::setParameter(const std::string & uniform, const glm::vec2 &value){
	use();
	int loc = location(uniform);
	glUniform2fv(loc, 1, glm::value_ptr(value));
}

void Program::setParameter(const std::string & uniform, const glm::vec3 &value){
	use();
	int loc = location(uniform);
	glUniform3fv(loc, 1, glm::value_ptr(value));
}

void Program::setParameter(const std::string & uniform, const glm::vec4 &value){
	use();
	int loc = location(uniform);
	glUniform4fv(loc, 1, glm::value_ptr(value));
}

void Program::setParameter(const std::string & uniform, const glm::mat4 &value){
	use();
	int loc = location(uniform);
	glUniformMatrix4fv(loc, 1, false, glm::value_ptr(value));
}

void Program::linkParameter(const std::string &str, const int *v){
	Program::triplet t;
	t.t = INT;
	t.s = str;
	t.v = (void*)v;

	_parameters.push_back(t);
}
void Program::linkParameter(const std::string &str, const float *v){
	Program::triplet t;
	t.t = FLOAT;
	t.s = str;
	t.v = (void*)v;

	_parameters.push_back(t);
}
void Program::linkParameter(const std::string &str, const glm::vec2 *v){
	Program::triplet t;
	t.t = VEC2;
	t.s = str;
	t.v = (void*)v;

	_parameters.push_back(t);
}
void Program::linkParameter(const std::string &str, const glm::vec3 *v){
	Program::triplet t;
	t.t = VEC3;
	t.s = str;
	t.v = (void*)v;

	_parameters.push_back(t);
}
void Program::linkParameter(const std::string &str, const glm::vec4 *v){
	Program::triplet t;
	t.t = VEC4;
	t.s = str;
	t.v = (void*)v;

	_parameters.push_back(t);
}
void Program::linkParameter(const std::string &str, const glm::mat4 *v){
	Program::triplet t;
	t.t = MAT4;
	t.s = str;
	t.v = (void*)v;

	_parameters.push_back(t);
}

void Program::setLinkedParameters(){
	for each (Program::triplet t in _parameters)
	{
		switch (t.t){
		case INT:
			setParameter(t.s, *reinterpret_cast<int*>(t.v));
			break;
		case FLOAT:
			setParameter(t.s, *reinterpret_cast<float*>(t.v));
			break;
		case VEC2:
			setParameter(t.s, *reinterpret_cast<glm::vec2*>(t.v));
			break;
		case VEC3:
			setParameter(t.s, *reinterpret_cast<glm::vec3*>(t.v));
			break;
		case VEC4:
			setParameter(t.s, *reinterpret_cast<glm::vec4*>(t.v));
			break;
		case MAT4:
			glm::mat4 v = *reinterpret_cast<glm::mat4*>(t.v);
			setParameter(t.s, *reinterpret_cast<glm::mat4*>(t.v));
			break;
		}
	}
}

int Program::location(const std::string &uniform){
	int val;
	if (_map.count(uniform) == 0){
		val = glGetUniformLocation(_id, uniform.c_str());
		_map[uniform] = val;
	}
	else{
		val = _map.find(uniform)->second;
	}
	return val;
}