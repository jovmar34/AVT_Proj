#pragma once
#include <unordered_map>
#include <map>
#include <string>
#include <sstream>
#include <fstream>
#include "shader.h"
#include "texture.h"

class Material {
private:

	std::map<int, Texture*> textures;
	
	unordered_map<std::string, Vector4D>	vals_Vec4;
	unordered_map<std::string, Vector3D>	vals_Vec3;
	unordered_map<std::string, Vector2D>	vals_Vec2;
	unordered_map<std::string, Matrix3>		vals_Mat3;
	unordered_map<std::string, Matrix4>		vals_Mat4;
	unordered_map<std::string, int>			vals_1int;
	unordered_map<std::string, float>		vals_1float;

public:
	Shader* shader;
	bool outline;

	Material(){};
	Material(Shader* _shader) : shader(_shader), outline(false) {};
	Material(Shader* _shader, bool _outline) : shader(_shader), outline(_outline){};

	void update(Matrix4 model_matrix, Matrix3 normal_matrix);

	void bind();
	void unbind();

	// Uniforms
	unordered_map<std::string, Vector4D> getValsVec4() { return vals_Vec4; }
	unordered_map<std::string, Vector3D> getValsVec3() { return vals_Vec3; }
	unordered_map<std::string, Vector2D> getValsVec2() { return vals_Vec2; }
	unordered_map<std::string, Matrix4> getValsMat4() { return vals_Mat4; }
	unordered_map<std::string, int> getVals1int() { return vals_1int; }
	unordered_map<std::string, float> getVals1float() { return vals_1float; }


	void setUniformVec4(std::string uniformName, Vector4D vec);
	void setUniformVec3(std::string uniformName, Vector3D vec);
	void setUniformVec2(std::string uniformName, Vector2D vec);
	void setUniformMat3(std::string uniformName, Matrix3 mat);
	void setUniformMat4(std::string uniformName, Matrix4 mat);
	void setUniform1int(std::string uniformName, int val);
	void setUniform1float(std::string uniformName, float val);

	// Textures
	void setTexture(Texture* texture, int channel = 0);
};