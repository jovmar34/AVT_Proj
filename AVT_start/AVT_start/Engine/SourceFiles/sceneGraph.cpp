#include "..\HeaderFiles\sceneGraph.h"

SceneGraph::SceneGraph()
{
	root = new SceneNode();
	current = root;

	root->transform = MxFactory::identity4();
	root->name = "root";
}

SceneGraph::~SceneGraph()
{
}

void SceneGraph::addChild(Object* obj, std::string name)
{
	addChild(obj, name, MxFactory::identity4());
}

void SceneGraph::addChild(Object* obj, std::string name, Matrix4 transform)
{
	SceneNode* child = new SceneNode();
	child->name = name;
	child->parent = current;
	child->obj = obj;

	if (obj) {
		obj->setTransform(transform);
		obj->saveInitTransform();
	}
	else child->transform = transform;
	
	current->children.push_back(child);
}

void SceneGraph::describe()
{
	SceneNode* curr;
	queue<SceneNode*> unvisited;
	unvisited.push(root);

	while (!unvisited.empty()) {
		curr = unvisited.front();
		unvisited.pop();

		for (SceneNode* child : curr->children) {
			unvisited.push(child);
		}

		std::cout << curr->getName() << std::endl;
		Matrix4 transf = curr->getTransform();
		std::cout << transf << std::endl;
	}
}

void SceneGraph::setCurr()
{
	current = current->children[current->children.size() - 1];
}

void SceneGraph::upLevels(int x)
{
	for (int i = 0; i < x; i++) {
		current = current->parent;
	}
}

void SceneGraph::setCurrToRoot()
{
	current = root;
}

void SceneGraph::setCamera(Camera* cam)
{
	this->cam = cam;
}

void SceneGraph::init(GLuint ProgramId)
{
	cam->setupCamera(ProgramId);

	SceneNode* curr;
	queue<SceneNode*> unvisited;
	unvisited.push(root);

	while (!unvisited.empty()) {
		curr = unvisited.front();
		unvisited.pop();

		for (SceneNode* child : curr->children) {
			unvisited.push(child);
		}

		if (curr->obj) curr->obj->initObject(ProgramId);
	}
}

void SceneGraph::draw()
{
	cam->drawCamera();

	SceneNode* curr;
	//stack<SceneNode*> unvisited;
	queue<SceneNode*> unvisited;
	unvisited.push(root);

	while (!unvisited.empty()) {
		curr = unvisited.front();
		//curr = unvisited.top();
		unvisited.pop();

		for (SceneNode* child : curr->children) {
			unvisited.push(child);
		}

		if (curr->obj) {
			Matrix4 transf = curr->getTransform();

			curr->obj->setTransform(curr->obj->initTransform * curr->parent->getTransform()); // FIXME: no work with animation!
			curr->obj->drawObject();
		}
	}
}

void SceneGraph::setTransform(Matrix4 transform)
{
	if (current->obj) current->obj->setTransform(transform);
	else current->transform = transform;
	
}

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
	Matrix4 transf = (obj == nullptr) ? transform : obj->transform;
	if (parent == nullptr) return transf;
	else {
		return transf * parent->getTransform();
	}
}
