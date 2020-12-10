#include "..\HeaderFiles\material.h"


void Material::update(Matrix4 model_matrix) 
{
	shader->setUniformMat4("ModelMatrix", model_matrix);
}

void Material::update(Matrix4 view_matrix, Matrix4 proj_matrix, Matrix4 model_matrix) 
{
	shader->setUniformMat4("ViewMatrix", view_matrix);
	shader->setUniformMat4("ProjectionMatrix", proj_matrix);
	shader->setUniformMat4("ModelMatrix", model_matrix);
}

// Apply all stored uniform values (and textures)
void Material::bind()
{
	shader->bind();

	if (albedo) {
		albedo->Bind();
		shader->setUniform1int("u_Texture", 0);
	}

	for (auto& it : vals_Vec4) {
		shader->setUniformVec4(it.first, it.second);
	}

	for (auto& it : vals_Vec3) {
		shader->setUniformVec3(it.first, it.second);
	}

	for (auto& it : vals_Vec2) {
		shader->setUniformVec2(it.first, it.second);
	}

	for (auto& it : vals_Mat4) {
		shader->setUniformMat4(it.first, it.second);
	}

	for (auto& it : vals_1int) {
		shader->setUniform1int(it.first, it.second);
	}

	for (auto& it : vals_1float) {
		shader->setUniform1float(it.first, it.second);
	}
}

void Material::unbind() {
	
	shader->unbind();

	if (albedo) albedo->Unbind();
}

// Set uniform values
void Material::setUniformVec4(std::string uniformName, Vector4D vec)
{
	vals_Vec4[uniformName] = vec;
}

void Material::setUniformVec3(std::string uniformName, Vector3D vec)
{
	vals_Vec3[uniformName] = vec;
}

void Material::setUniformVec2(std::string uniformName, Vector2D vec)
{
	vals_Vec2[uniformName] = vec;
}

void Material::setUniformMat4(std::string uniformName, Matrix4 mat)
{
	vals_Mat4[uniformName] = mat;
}

void Material::setUniform1int(std::string uniformName, int val)
{
	vals_1int[uniformName] = val;
}

void Material::setUniform1float(std::string uniformName, float val)
{
	vals_1float[uniformName] = val;
}

void Material::setAlbedoTexture(Texture* _albedo) 
{
	albedo = _albedo;
}