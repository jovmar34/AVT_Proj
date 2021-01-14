#pragma once

#include <string>
#include "matrix.h"
#include "mesh.h"
#include "material.h"

struct SceneNode {
	SceneNode* parent;
	std::vector<SceneNode*> children;
	Mesh* mesh = nullptr;
	Matrix4 transform = MxFactory::identity4();
	Material* material = nullptr;
	Material* outline = nullptr;
	bool selected = true;

	//Debug thingies
	std::string name;
	std::string meshFile = "None";
	std::string meshName = "None";
	std::string materialName = "None";
	std::string shaderName = "None";
	std::string vertexShaderFile = "None";
	std::string fragmentShaderFile = "None";

	std::string getName();
	Matrix4 getTransform();
	void init();
};
