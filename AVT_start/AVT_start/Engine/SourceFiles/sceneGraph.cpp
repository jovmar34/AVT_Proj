#include "..\HeaderFiles\sceneGraph.h"

SceneGraph::SceneGraph()
{
	root = new SceneNode();
	current = root;

	root->transform = MxFactory::identity4();
	root->name = "root";
	nameMap[root->name] = root;
}

SceneGraph::~SceneGraph()
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
	}
}

void SceneGraph::addChild(Material* material, Mesh* mesh, std::string name)
{
	addChild(material, mesh, name, MxFactory::identity4());
}

void SceneGraph::addChild(Material* material, Mesh* mesh, std::string name, Matrix4 transform)
{
	SceneNode* child = new SceneNode();
	child->name = name;
	child->parent = current;
	child->mesh = mesh;
	child->transform = transform;
	child->material = material;
	
	current->children.push_back(child);

	nameMap[name] = child;
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

void SceneGraph::setCurr(std::string name)
{
	current = nameMap[name];
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

void SceneGraph::saveCurr()
{
	nameMap[current->name] = current;
}

Camera* SceneGraph::getCam()
{
	return cam;
}

void SceneGraph::init(GLuint ProgramId)
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

		if (curr->mesh) curr->mesh->init();
	}
}

void SceneGraph::draw()
{
	SceneNode* curr;
	queue<SceneNode*> unvisited;
	bool update = cam->change;

	unvisited.push(root);

	while (!unvisited.empty()) {
		curr = unvisited.front();
		unvisited.pop();

		for (SceneNode* child : curr->children) {
			unvisited.push(child);
		}

		if (curr->mesh) {

			curr->material->bind();

			if (update) 
			{
				curr->material->update(cam->view, cam->projection, curr->getTransform());
			}
			else 
			{
				curr->material->update(curr->getTransform());
			}
			
			curr->mesh->draw();

			curr->material->unbind();
		}
	}
}

void SceneGraph::setTransform(std::string node, Matrix4 transform)
{
	nameMap[node]->transform = transform;
}

void SceneGraph::applyTransform(std::string node, Matrix4 transform)
{
	nameMap[node]->transform = transform * nameMap[node]->transform;
}
