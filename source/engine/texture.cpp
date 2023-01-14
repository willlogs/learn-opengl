#ifndef HIGINE_TEXTURE
#define HIGINE_TEXTURE

#include "common.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../stb_image.h"

using namespace std;

class texture : public utils::idable
{
private:
	int width, height, nrChannels;
	unsigned char *data;

public:
	texture();
	texture(const char *path, GLenum format);
	~texture();
};

texture::texture()
{
}

texture::texture(const char *path, GLenum format){
	data = stbi_load(path, &width, &height, &nrChannels, 0);

	if(data){
		// generate and bind to context
		glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_2D, id);

		// fill in the texture part of the context with data
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		// generate mipmaps
		glGenerateMipmap(GL_TEXTURE_2D);

		// once the data is copied to context, it can be released
		stbi_image_free(data);
	}
	else{
		cout << "trouble loading textures" << endl;
	}
}

texture::~texture()
{
}

#endif