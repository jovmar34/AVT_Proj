#pragma once
#include <GL\glew.h>
#include <string>
#include <fstream>
#include <sstream>
#include "matrix.h"
#include <vector>

struct ShaderSource {
	std::string VertexSource;
	std::string FragmentSource;
};


class Shader {
private:
	GLuint m_shaderId;
	std::string m_shaderPath;
public:
	Shader(const std::string& filepath);
	~Shader();

	void Bind();
	void Unbind();
	void setUniformMatrix(const std::string& name, Matrix4 mat);

private:
	GLuint getUniformLocation(const std::string& name);
	ShaderSource parseShader(const std::string& filepath);
	GLuint CompileShader(GLuint type, const std::string& source);
};