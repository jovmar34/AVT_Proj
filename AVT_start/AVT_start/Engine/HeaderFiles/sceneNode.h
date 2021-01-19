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
	Matrix4 inverse = MxFactory::identity4();
	Material* material = nullptr;
	Material* outline = nullptr;
	bool selected = true;
	unsigned int id = -1;

	TransformInfo parentInfo = { MxFactory::identity4(), MxFactory::identity4() };

	//Debug thingies
	std::string name;
	std::string meshFile = "None";
	std::string meshName = "None";
	std::string materialName = "None";
	std::string shaderName = "None";
	std::string vertexShaderFile = "None";
	std::string fragmentShaderFile = "None";
	std::string textureName = "None";
	std::string textureFile = "None";

	std::string getName();
	Matrix4 getTransform();
	Matrix4 getInverse();
	TransformInfo getTransformInfo();
	Matrix3 getNormal();
	void init();
};
