#include "Shader.h"


Shader::Shader(GLenum shaderType)
{
	_id = glCreateShader(shaderType);
}

Shader::~Shader()
{
	glDeleteShader(_id);
}

const GLuint Shader::getId(){
	return _id;
}

void Shader::load(const std::string &path){
	GLchar* shaderSource;
	unsigned long len;

	std::ifstream file;
	file.open(path.c_str(), std::ios::in); // opens as ASCII!
	if (!file) {
		printf("Error: shader file not found %s!", path.c_str()); throw 53;
	}

	len = Shader::getFileLength(file);
	if (len == 0) {
		printf("Error: empty shader file %s!", path.c_str()); throw 53;
	}

	shaderSource = new char[len + 1];
	if (shaderSource == 0)  {
		printf("Error: shader string allocation error %s!", path.c_str()); throw 53;
	}

	printf("Loading %s\n", path.c_str());

	// len isn't always strlen cause some characters are stripped in ascii read...
	// it is important to 0-terminate the real length later, len is just max possible value... 
	shaderSource[len] = 0;

	unsigned int i = 0;
	while (file.good()) {
		shaderSource[i] = file.get();       // get character from file.
		if (!file.eof())
			i++;
	}

	shaderSource[i] = 0;  // 0-terminate it at the correct position

	file.close();

	glShaderSource(_id, 1, (const char **)&shaderSource, NULL);

	delete[] shaderSource;
}

void Shader::compile(){
	glCompileShader(_id);
}

std::string Shader::getLog(){
	int infologLength = 0;
	int maxLength;

	glGetShaderiv(_id, GL_INFO_LOG_LENGTH, &maxLength);

	char *infoLog = new char[maxLength];

	glGetShaderInfoLog(_id, maxLength, &infologLength, infoLog);

	std::string log(infoLog);
	
	delete[] infoLog;

	return log;
}

////////////////////////////////////////
// shader file loading
unsigned long Shader::getFileLength(std::ifstream &file)
{
	if (!file.good()) return 0;

	file.seekg(0, std::ios::end);
	unsigned long len = file.tellg();
	file.seekg(std::ios::beg);

	return len;
}