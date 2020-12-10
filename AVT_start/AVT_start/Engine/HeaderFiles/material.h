#pragma once
#include <unordered_map>
#include <string>
#include <sstream>
#include <fstream>
#include "shader.h"
#include "texture.h"

class Material {
private:
	
	Shader* shader;
	Texture* albedo;
	
	unordered_map<std::string, Vector4D>	vals_Vec4;
	unordered_map<std::string, Vector3D>	vals_Vec3;
	unordered_map<std::string, Vector2D>	vals_Vec2;
	unordered_map<std::string, Matrix4>		vals_Mat4;
	unordered_map<std::string, int>			vals_1int;
	unordered_map<std::string, float>		vals_1float;

public:
	Material(Shader* _shader) : shader(_shader), albedo(nullptr) {};

	void update(Matrix4 model_matrix);
	void update(Matrix4 view_matrix, Matrix4 proj_matrix, Matrix4 model_matrix);

	void bind();
	void unbind();

	// Uniforms
	void setUniformVec4(std::string uniformName, Vector4D vec);
	void setUniformVec3(std::string uniformName, Vector3D vec);
	void setUniformVec2(std::string uniformName, Vector2D vec);
	void setUniformMat4(std::string uniformName, Matrix4 mat);
	void setUniform1int(std::string uniformName, int val);
	void setUniform1float(std::string uniformName, float val);

	// Textures
	void setAlbedoTexture(Texture* _albedo);
};