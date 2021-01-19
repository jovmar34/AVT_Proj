#pragma once


#include <iostream>
#include <string>
#include "sceneGraph.h"
#include "sceneNode.h"
#include "camera.h"
#include <fstream>

struct NodeDescription {
	TransformInfo myTransf;
	std::string mesh_name, material_name,
		node_name, parent_name;
};

class SceneSerializer {
private:
	Camera* _camera;
	Manager* _manager;
	SceneNode* _parent;

public:
	SceneSerializer(Camera* cam, Manager* man, SceneNode* par);
	SceneSerializer(SceneNode* par);
	SceneSerializer(Camera* cam);
	SceneSerializer();
	~SceneSerializer();

	void setCamera(Camera* cam) { _camera = cam; }
	void setManager(Manager* man) { _manager = man; }
	void setParent(SceneNode* par) { _parent = par; }

	void serializeCamera(std::ofstream& out);
	void serializeManager(std::ofstream& out);
	void serializeNode(SceneNode* node, std::ofstream& out);

	void newSerialize(const std::string& filepath);
	vector<NodeDescription*> newDeserialize(const std::string& filepath);
};
