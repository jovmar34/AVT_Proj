#include "..\HeaderFiles\material.h"


void Material::update(Matrix4 model_matrix, Matrix3 normal_matrix) 
{
	shader->setUniformMat4("ModelMatrix", model_matrix);
	shader->setUniformMat3("NormalMatrix", normal_matrix);
}


// Apply all stored uniform values (and textures)
void Material::bind()
{
	shader->bind();

	if (!textures.empty()) {

		for(auto &item : textures) {

			item.second->Bind(item.first);
			shader->setUniform1int("u_Texture", item.first);
		}
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

	for (auto& it : vals_Mat3) {
		shader->setUniformMat3(it.first, it.second);
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

	if (!textures.empty()) {

		for (auto& item : textures) {

			item.second->Unbind();
		}
	}
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

void Material::setUniformMat3(std::string uniformName, Matrix3 mat)
{
	vals_Mat3[uniformName] = mat;
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

void Material::setTexture(Texture* texture, int channel) 
{
	textures[channel] = texture;
}