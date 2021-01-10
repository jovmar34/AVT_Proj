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
#include "../HeaderFiles/manager.h"

class SceneGraph {
	SceneNode* root = nullptr;
	SceneNode* current = nullptr;
	Camera* cam = nullptr;
	unordered_map<std::string, SceneNode*> nameMap;
	unordered_map<unsigned int, SceneNode*> idMap;

	Material* outline;
	SceneNode* grid = nullptr;
	SceneNode* gizmo = nullptr;
	double dist = 0;
	unsigned int selected = 0;

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
	void setGrid(Material* mat, Mesh* mesh, TransformInfo info);
	void setGizmo(Material* mat, Mesh* mesh);
	void setDist(double val) { dist = val; };
	void setSelected(unsigned int selected);

	Camera* getCam();

	void init(GLuint ProgramId);
	void draw();

	void setTransform(std::string node, Matrix4 transform);
	void applyTransform(std::string node, Matrix4 transform);

	void setTransforms(std::string node, vector<TransformInfo> transforms);
	void applyTransforms(std::string node, vector<TransformInfo> transforms);

	SceneNode* getNode(std::string name);
	SceneNode* getSelected();
	
	void changeParent(std::string node, std::string newParent);

	// Debug
	void describe();

	// specifics
	void drawGizmos(Vector3D pos);
};