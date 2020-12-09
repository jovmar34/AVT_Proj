#include "../HeaderFiles/sceneNode.h"

std::string SceneNode::getName()
{
	if (parent == nullptr) return name;
	else {
		stringstream stream;
		stream << parent->getName() << "::" << name;
		return stream.str();
	}
}

Matrix4 SceneNode::getTransform()
{
	if (parent == nullptr) return transform;
	else {
		return parent->getTransform() * transform;
	}
}

void SceneNode::init()
{
	if (mesh) mesh->init();
}
