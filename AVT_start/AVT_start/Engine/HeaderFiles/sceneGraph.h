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


struct SceneNode {
	SceneNode* parent;
	std::vector<SceneNode*> children;
	Object* obj = nullptr;
	Matrix4 transform = MxFactory::identity4();

	//Debug thingies
	std::string name;

	std::string getName();
	Matrix4 getTransform();
};

class SceneGraph {
	SceneNode* root = nullptr;
	SceneNode* current = nullptr;
	Camera* cam = nullptr;
	unordered_map<std::string, SceneNode*> nameMap;

public:
	SceneGraph();
	~SceneGraph();

	void addChild(Object* obj, std::string name);
	void addChild(Object* obj, std::string name, Matrix4 transform);
	void setCurr();
	void upLevels(int x);
	void setCurrToRoot();
	void setCamera(Camera* cam);
	void saveCurr();

	void init(GLuint ProgramId);
	void draw();

	void setTransform(Matrix4 transform);

	// Animation thingies
	void animateFrame(double time);
	void animateCubes(double time);
	
	// Debug
	void describe();
};