#ifndef HIGINE_SHADER_PROGRAM
#define HIGINE_SHADER_PROGRAM

#include "../common.h"
#include "shader.cpp"

class shaderProgram : public utils::idable
{
private:
	shader* vertex;
	shader* fragment;

public:

	shaderProgram();
	shaderProgram(shader* vertex, shader* fragment);
	~shaderProgram();
};

shaderProgram::shaderProgram()
{
}

shaderProgram::shaderProgram(shader* vertex, shader* fragment){
	this->vertex = vertex;
	this->fragment = fragment;

	id = glCreateProgram();
	glAttachShader(id, vertex->get_id());
	glAttachShader(id, fragment->get_id());
}

shaderProgram::~shaderProgram()
{
}


#endif