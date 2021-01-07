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

Matrix3 SceneNode::getNormal()
{
	Matrix4 transf4 = getTransform();
	Matrix3 transf3 = transf4.decrease();

	Matrix3 normal = transf3.transpose().inverse();

	return normal;
}

void SceneNode::init()
{
	if (mesh) mesh->init();
}
