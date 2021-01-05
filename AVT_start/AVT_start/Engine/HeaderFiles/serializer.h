#pragma once


#include <iostream>
#include <string>
#include "sceneGraph.h"
#include "sceneNode.h"
#include "camera.h"
#include <fstream>

class SceneSerializer {
private:
	Camera* _camera;
	SceneNode* _parent;

public:
	SceneSerializer(Camera* cam, SceneNode* par);
	SceneSerializer(SceneNode* par);
	SceneSerializer(Camera* cam);
	SceneSerializer();
	~SceneSerializer();

	void setCamera(Camera* cam) { _camera = cam; }
	void setParent(SceneNode* par) { _parent = par; }

	void serializeCamera(std::ofstream& out);
	void serializeNode(SceneNode* node, std::ofstream& out);
	void serialize(const std::string& filepath);
	void deserialize(const std::string& filepath);

};

