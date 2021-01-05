#include "..\HeaderFiles\serializer.h"

SceneSerializer::SceneSerializer(Camera* cam, SceneNode* par) {
	_camera = cam;
	_parent = par;
}

SceneSerializer::SceneSerializer(Camera* cam) {
	_camera = cam;
}

SceneSerializer::SceneSerializer(SceneNode* par) {
	_parent = par;
}

SceneSerializer::~SceneSerializer()
{
//?
}

void SceneSerializer::serializeCamera(std::ofstream& out)
{
	//_camera->projType
	out << "Camera:\n" << "- Type: " << "todo" << "\n- View Matrix: " << _camera->getView().toString() << "\n- Projection Matrix: " << _camera->getProjection().toString() << "\n- InvView Matrix: " << _camera->getInvView().toString() << std::endl;
}

void SceneSerializer::serializeNode(SceneNode* node, std::ofstream& out)
{
	out << "Node:\n" << "- Name: " << node->getName() << "\n- Children: " << node->children.size() << "\n- Transformation: " << node->getTransform().toString() << std::endl;
}

void SceneSerializer::serialize(const std::string& filepath)
{
	SceneNode* n;
	std::ofstream file(filepath);
	serializeCamera(file);
	file << "Node:\n" << "- Name: " << _parent->getName() << "\n- Children: " << _parent->children.size() << "\n- Transformation: " << _parent->getTransform().toString() << std::endl;

	for (int i = 0; i < _parent->children.size(); i++) {
		n = _parent->children[i];
		serializeNode(n, file);
	}
	file.close();
}

void SceneSerializer::deserialize(const std::string& filepath)
{
	std::ifstream file(filepath, ios::in);
	std::string line;
	while (std::getline(file, line))
	{
		std::istringstream iss(line);
		cout << line << endl;
	}

	file.close();
}