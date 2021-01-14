#pragma once
#include <string>

class Texture 
{
private:
	unsigned int renderer_ID;
	std::string name = "None";
	std::string file_path;
	unsigned char* local_buffer;
	int width, height, bpp;

public:
	Texture(const std::string& n, const std::string& path);
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

	inline int GetWidth() const { return width; }
	inline int GetHeight() const { return height; }
};