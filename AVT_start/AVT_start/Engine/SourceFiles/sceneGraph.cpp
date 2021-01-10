#include "..\HeaderFiles\sceneGraph.h"

SceneGraph::SceneGraph()
{
	root = new SceneNode();
	current = root;

	root->transform = MxFactory::identity4();
	root->name = "root";
	nameMap[root->name] = root;
	idMap[0] = nullptr;
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
	if (child->mesh) {
		child->id = Manager::getInstance()->getCounter();
		idMap[child->id] = child;
	}
	
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

void SceneGraph::setOutline(Material* mat) {
	outline = mat;
}

void SceneGraph::setSelected(unsigned int selected)
{
	this->selected = selected;
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

	cam->drawCamera();
	Matrix3 inv = cam->invView.decrease();

	unvisited.push(root);
	glClearStencil(0);
	glClear(GL_STENCIL_BUFFER_BIT);

	glEnable(GL_STENCIL_TEST);

	while (!unvisited.empty()) {
		curr = unvisited.front();
		unvisited.pop();

		for (SceneNode* child : curr->children) {
			unvisited.push(child);
		}

		if (curr->mesh) {

			curr->material->bind();

			TransformInfo info = curr->getTransformInfo();
			Matrix3 transpinv = info.inverse.transpose().decrease();
			curr->material->update(info.transform, inv.transpose() * transpinv); // FIXME: sceneNode remove getNormal
			
			glStencilFunc(GL_ALWAYS, curr->id, 0xFF);
			glStencilOp(GL_ZERO, GL_KEEP, GL_REPLACE);

			curr->mesh->draw();

			curr->material->unbind();

			// Draw Outline
			if (selected == curr->id) 
			{
				outline->bind();
				outline->update(curr->getTransform(), curr->getNormal());
				glCullFace(GL_FRONT);
				curr->mesh->draw();
				glCullFace(GL_BACK);
				outline->unbind();
			}
		}
	}

	glDisable(GL_STENCIL_TEST);
}

void SceneGraph::setTransform(std::string node, Matrix4 transform)
{
	nameMap[node]->transform = transform;
}

void SceneGraph::applyTransform(std::string node, Matrix4 transform)
{
	nameMap[node]->transform = transform * nameMap[node]->transform;
}

void SceneGraph::setTransforms(std::string node, vector<TransformInfo> transforms)
{
	SceneNode* changed = nameMap[node];

	Matrix4 transf = MxFactory::identity4();
	Matrix4 inv = MxFactory::identity4();

	for (auto info : transforms) {
		transf = info.transform * transf;
		inv = inv * info.inverse;
	}

	changed->transform = transf;
	changed->inverse = inv;
}

void SceneGraph::applyTransforms(std::string node, vector<TransformInfo> transforms)
{
	SceneNode* changed = nameMap[node];

	Matrix4 transf = MxFactory::identity4();
	Matrix4 inv = MxFactory::identity4();

	for (auto info : transforms) {
		transf = info.transform * transf;
		inv = inv * info.inverse;
	}

	changed->transform = transf * changed->transform;
	changed->inverse = changed->inverse * inv;
}

SceneNode* SceneGraph::getNode(std::string name)
{
	return nameMap[name];
}

SceneNode* SceneGraph::getSelected()
{
	return idMap[selected];
}

void SceneGraph::changeParent(std::string node, std::string newParent)
{
	SceneNode* changed = nameMap[node];
	SceneNode* origParentNode = changed->parent;
	SceneNode* newParentNode = nameMap[newParent];

	if (origParentNode == newParentNode) {
		std::cout << "same" << std::endl;
		return;
	}

	origParentNode->children.erase(std::remove(origParentNode->children.begin(), origParentNode->children.end(), changed), origParentNode->children.end());
	
	changed->parent = newParentNode;
	newParentNode->children.push_back(changed);

}
