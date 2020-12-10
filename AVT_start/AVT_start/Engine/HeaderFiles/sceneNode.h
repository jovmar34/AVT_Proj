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
	Material *material = nullptr;

	//Debug thingies
	std::string name;

	std::string getName();
	Matrix4 getTransform();
	void init();
};
