#pragma once

#define _USE_MATH_DEFINES

#include <vector>
#include <string>
#include <sstream>
#include <queue>
#include <stack>
#include <cmath>
#include <unordered_map>
#include "matrix.h"
#include "camera.h"
#include "mxfactory.h"
#include "object.h"
#include "shader.h"
#include "sceneNode.h"

class SceneGraph {
	SceneNode* root = nullptr;
	SceneNode* current = nullptr;
	Camera* cam = nullptr;
	unordered_map<std::string, SceneNode*> nameMap;

public:
	SceneGraph();
	~SceneGraph();

	void addChild(Shader* shader, Mesh* mesh, std::string name);
	void addChild(Shader* shader, Mesh* mesh, std::string name, Matrix4 transform);
	void setCurr(std::string name);
	void upLevels(int x);
	void setCurrToRoot();
	void setCamera(Camera* cam);
	void saveCurr();

	void init(GLuint ProgramId);
	void draw();

	void setTransform(std::string node, Matrix4 transform);
	void applyTransform(std::string node, Matrix4 transform);
	
	// Debug
	void describe();
};