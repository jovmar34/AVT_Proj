#pragma once

#include <vector>
#include <string>
#include <sstream>
#include <queue>
#include <stack>
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

public:
	SceneGraph();
	~SceneGraph();

	void addChild(Object* obj, std::string name);
	void addChild(Object* obj, std::string name, Matrix4 transform);
	void setCurr();
	void upLevels(int x);
	void setCurrToRoot();
	void setCamera(Camera* cam);

	void init(GLuint ProgramId);
	void draw();

	void setTransform(Matrix4 transform);
	
	// Debug
	void describe();
};