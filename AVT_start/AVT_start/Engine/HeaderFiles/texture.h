#pragma once
#include <string>

class Texture 
{
private:
	unsigned int renderer_ID;
	std::string name = "None";
	unsigned char* local_buffer;
	int width, height, bpp;

public:
	std::string file_path;
	Texture(const std::string& n, const std::string& path);
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

	inline int GetWidth() const { return width; }
	inline int GetHeight() const { return height; }
};