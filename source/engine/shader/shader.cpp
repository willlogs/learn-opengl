#ifndef HIGINE_SHADER
#define HIGINE_SHADER

#include "../common.h"
#include "fstream"

using namespace std;

class shader : public utils::idable
{
private:
	string path;

	void read_from_path();

public:
	const char* content;
	string shader_content = "";
	GLenum type = GL_VERTEX_SHADER;

	shader();
	shader(string path, GLenum type);
	~shader();
	void compile();
	void check_compilation();
	void delete_shader();
};

shader::shader(){}

shader::shader(string path, GLenum type)
{
	this->path = path;
	this->type = type;
	read_from_path();
}

shader::~shader()
{
}

void shader::read_from_path(){
	shader_content = "";
	string line = "";
	ifstream read_stream(path);

	if(read_stream.fail()){
		cout << "failed reading shader file: " << strerror(errno) << endl;
	}

	while(getline(read_stream, line)){
		shader_content.append(line);
		shader_content.append("\n");
	}

	read_stream.close();
	content = &shader_content[0];
}

void shader::compile(){
	id = glCreateShader(type);
	const char* sh = &shader_content[0];
	glShaderSource(id, 1, &sh, NULL);
	glCompileShader(id);
}

void shader::check_compilation(){
	int success;
	char infoLog[512];
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	if(!success){
		glGetShaderInfoLog(id, 512, NULL, infoLog);
		cout << "ERROR::SHADER::COMPILATION_FAILED" << infoLog << endl;
	}
}

void shader::delete_shader(){
	glDeleteShader(id);
}

#endif