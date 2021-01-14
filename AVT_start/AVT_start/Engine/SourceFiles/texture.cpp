#include "..\HeaderFiles\texture.h"
#include "..\Vendor\stb_image\stb_image.h"

#include <GL/glew.h>
#include <iostream>

void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogcall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpengGL Error] (" << error << "): " << function <<
			" " << file << ":" << line << std::endl;
		return false;
	}
	return true;
}

Texture::Texture(const std::string& n, const std::string& path)
	: renderer_ID(0), name(n), file_path(path), local_buffer(nullptr), width(0), height(0), bpp(0)
{
	stbi_set_flip_vertically_on_load(1);
	local_buffer = stbi_load(path.c_str(), &width, &height, &bpp, 4);

	glGenTextures(1, &renderer_ID);
	glBindTexture(GL_TEXTURE_2D, renderer_ID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, local_buffer);
	glBindTexture(GL_TEXTURE_2D, 0);

	if (local_buffer) {
		stbi_image_free(local_buffer);
	}
}

Texture::~Texture()
{
	glDeleteTextures(1, &renderer_ID);
}

void Texture::Bind(unsigned int slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, renderer_ID);
}

void Texture::Unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}


