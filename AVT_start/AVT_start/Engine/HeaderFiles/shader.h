#pragma once
#include <unordered_map>
#include <string>
#include <sstream>
#include <fstream>
#include "vector.h"
#include "matrix.h"


class Shader {
private:
	GLuint programId;
	unordered_map<std::string, GLuint> uniforms;

	static std::string parseShader(const std::string filename);
	static GLuint compileShader(GLuint type, const std::string& source);
	GLuint getUniformLocation(std::string name);
public:
	Shader(const std::string vertexFile, const std::string fragmentFile);
	~Shader();

	void bind();
	void unbind();

	// Uniforms
	void addUniformBlock(std::string uniformName, unsigned int binding);
	void setUniformVec4(std::string uniformName, Vector4D vec);
	void setUniformVec3(std::string uniformName, Vector3D vec);
	void setUniformVec2(std::string uniformName, Vector2D vec);
	void setUniformMat3(std::string uniformName, Matrix3 mat);
	void setUniformMat4(std::string uniformName, Matrix4 mat);
	void setUniform1int(std::string uniformName, int val);
	void setUniform1float(std::string uniformName, float val);
};