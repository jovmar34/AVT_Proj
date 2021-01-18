#pragma once

#include <unordered_map>
#include <string>
#include "GL/glew.h"
#include "shader.h"
#include "mesh.h"
#include "texture.h"
#include "material.h"


class Manager {
protected:
	static Manager* instance;
	std::unordered_map<std::string, Shader*> shaders;
	std::unordered_map<std::string, Mesh*> meshes;
	std::unordered_map<std::string, Texture*> textures;
	std::unordered_map<std::string, Material*> materials;
	unsigned int counter = 1;

	~Manager() {
		shaders.clear();
		meshes.clear();
		textures.clear();
		materials.clear();
	}

public:
	static Manager* getInstance() {
		if (instance == nullptr) 
			instance = new Manager();
		return instance;
	}

	static void destroy() {
		if (instance != nullptr)
			delete instance;
	}

	Shader* addShader(std::string name, Shader* shader) {
		shaders[name] = shader;
		return shader;
	}

	Mesh* addMesh(std::string name, Mesh* mesh) {
		meshes[name] = mesh;
		return mesh;
	}

	Texture* addTexture(std::string name, Texture* texture) {
		textures[name] = texture;
		return texture;
	}

	Material* addMaterial(std::string name, Material* material) {
		materials[name] = material;
		return material;
	}

	Shader* getShader(std::string name) {
		return shaders[name];
	}

	Mesh* getMesh(std::string name) {
		return meshes[name];
	}

	Texture* getTexture(std::string name) {
		return textures[name];
	}

	Material* getMaterial(std::string name) {
		return materials[name];
	}

	void init() {
		for (auto mesh_entry : meshes) {
			mesh_entry.second->init();
		}
	}

	unsigned int getCounter() {
		return counter; //removed ++ otherwise new obj would increase +2
	}
	void incCounter() {
		counter++; 
	}
	bool hasMesh(string meshname) {
		return meshes.find(meshname) != meshes.end();
	}
};