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
	if (parent == nullptr) 
		return transform;
	else {
		return parent->getTransform() * transform;
	}
}

Matrix3 SceneNode::getNormal()
{
	Matrix4 transf4 = getTransform();
	Matrix3 transf3 = transf4.decrease();

	Matrix3 normal = transf3.inverse().transpose();

	return normal;
}

TransformInfo SceneNode::getTransformInfo()
{
	if (parent == nullptr)
		return { transform, inverse };
	else {
		TransformInfo info = parent->getTransformInfo();
		return { info.transform * transform, inverse * info.inverse };
	}
}

void SceneNode::init()
{
	if (mesh) mesh->init();
}
