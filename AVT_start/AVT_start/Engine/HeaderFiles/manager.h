#pragma once

#include <unordered_map>
#include <string>
#include "GL/glew.h"
#include "shader.h"
#include "mesh.h"
#include "texture.h"


class Manager {
protected:
	static Manager* instance;
	std::unordered_map<std::string, Shader*> shaders;
	std::unordered_map<std::string, Mesh*> meshes;
	std::unordered_map<std::string, Texture*> textures;

	~Manager() {
		shaders.clear();
		meshes.clear();
		textures.clear();
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

	void addShader(std::string name, Shader* shader) {
		shaders[name] = shader;
	}

	void addMesh(std::string name, Mesh* mesh) {
		meshes[name] = mesh;
	}

	void addTexture(std::string name, Texture* texture) {
		textures[name] = texture;
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
};

Manager* Manager::instance = 0;