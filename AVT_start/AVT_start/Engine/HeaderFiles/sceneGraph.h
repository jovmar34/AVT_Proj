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
#include "manager.h"
#include "serializer.h"

class SceneGraph {
	SceneNode* root = nullptr;
	SceneNode* current = nullptr;
	Camera* cam = nullptr;
	unordered_map<std::string, SceneNode*> nameMap;

	Material* outline;

public:
	SceneGraph();
	~SceneGraph();

	void addChild(Material* material, Mesh* mesh, std::string name);
	void addChild(Material* material, Mesh* mesh, std::string name, Matrix4 transform);
	void setCurr(std::string name);
	void upLevels(int x);
	void setCurrToRoot();
	void setCamera(Camera* cam);
	void saveCurr();
	void setOutline(Material* mat);

	Camera* getCam();

	void init(GLuint ProgramId);
	void draw();

	void setTransform(std::string node, Matrix4 transform);
	void applyTransform(std::string node, Matrix4 transform);

	SceneNode* getNode(std::string name);
	
	void changeParent(std::string node, std::string newParent);

	// Debug
	void describe();

	void serializeScene(Camera* cam, Manager* man, const std::string& filepath);
	void loadScene(const std::string& filepath);
};