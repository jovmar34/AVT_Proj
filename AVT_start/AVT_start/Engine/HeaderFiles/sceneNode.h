#pragma once

#include <string>
#include "matrix.h"
#include "mesh.h"
#include "shader.h"

struct SceneNode {
	SceneNode* parent;
	std::vector<SceneNode*> children;
	Mesh* mesh = nullptr;
	Matrix4 transform = MxFactory::identity4();
	Shader *myShader = nullptr;

	//Debug thingies
	std::string name;

	std::string getName();
	Matrix4 getTransform();
	void init();
};
