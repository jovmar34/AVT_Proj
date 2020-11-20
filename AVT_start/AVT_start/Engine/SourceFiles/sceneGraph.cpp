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

		if (curr->obj)
			delete curr->obj;
	}
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

void SceneGraph::saveCurr()
{
	nameMap[current->name] = current;
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
	queue<SceneNode*> unvisited;
	unvisited.push(root);

	while (!unvisited.empty()) {
		curr = unvisited.front();
		unvisited.pop();

		for (SceneNode* child : curr->children) {
			unvisited.push(child);
		}

		if (curr->obj) {
			Matrix4 transf = curr->getTransform();

			curr->obj->drawObject(transf);
		}
	}
}

void SceneGraph::setTransform(Matrix4 transform)
{
	if (current->obj) current->obj->setTransform(transform);
	else current->transform = transform;
	
}

// time in range [0,1]
void SceneGraph::animateFrame(double time) 
{
	SceneNode* master = nameMap["frame"];
	double angle = time * 360; // in degrees

	Matrix4 transform = MxFactory::rotation4(Vector3D(0,1,0), angle);

	master->obj->transform = transform * master->obj->initTransform;
}

double remap(double val, double low1, double high1 , double low2, double high2) {
	return low2 + (val - low1) * (high2 - low2) / (high1 - low1);
}

// time in range [0,1]
void SceneGraph::animateCubes(double angle)
{
	vector<SceneNode*> cubes = nameMap["cube_container"]->children;

	double offset_factor = 0.5; 
	double amplitude = 2.0;

	angle = remap(angle, 0, 2 * M_PI, -M_PI / 2, 5 * M_PI_2);

	for (int i = 0; i < cubes.size(); i++) {
		
		SceneNode* cubei = cubes[i];
		Matrix4 init = cubei->obj->initTransform;
		Vector3D dir = cubei->obj->getBasePosition();
		dir.z = 0;
		dir.normalize();

		double cube_angle = atan2(dir.y, dir.x) - atan2(1, 0);
		if (cube_angle < 0) cube_angle += 2 * M_PI;

		double alpha = angle - cube_angle;
		double val = exp(-pow(amplitude * alpha, 2));

		Vector3D translate_vec = dir * val;
		Matrix4 new_transform = MxFactory::translation4(translate_vec) * init;

		cubei->obj->setTransform(new_transform);

	}
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
		return parent->getTransform() * transf;
	}
}
