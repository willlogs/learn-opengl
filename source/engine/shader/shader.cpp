#ifndef HIGINE_SHADER
#define HIGINE_SHADER

#include "../common.h"
#include "fstream"

using namespace std;

class shader
{
private:
	string path;

	void read_from_path();

public:
	const char* content;
	string shader_content = "";

	shader();
	shader(string path);
	~shader();
};

shader::shader(){}

shader::shader(string path)
{
	this->path = path;
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
#endif