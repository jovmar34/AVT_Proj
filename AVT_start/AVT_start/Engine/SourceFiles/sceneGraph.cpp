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
		Manager* h = Manager::getInstance();
		child->id = h->getCounter();
		idMap[child->id] = child;
		h->incCounter();
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

void SceneGraph::drawGizmos()
{
	SceneNode* sel = getSelected();
	Vector3D absPos = (sel->getTransformInfo().transform * Vector4D(0, 0, 0, 1)).to3D(),
		relPos = (sel->transform * Vector4D(0, 0, 0, 1)).to3D();

	if (gizmoActive) return;

	Manager* h = Manager::getInstance();
	Shader* shader = h->getShader("gizmo_shader");
	int sign = 1;
	Mesh* mesh = h->getMesh("translation_gizmo");
	if (gizmoType == GizmoType::Rotation) {
		sign = -1;
		mesh = h->getMesh("rotation_gizmo");
	}
	if (gizmoType == GizmoType::Scaling) mesh = h->getMesh("scale_gizmo");

	Vector3D color;
	double percentage = (cam->eye - absPos).length() / dist;
	Matrix4 model,
		rotate = MxFactory::identity4(),
		scale = MxFactory::scaling4(percentage * Vector3D(1.5,1.5,1.5)),
		translate = MxFactory::translation4(absPos);


	glDisable(GL_DEPTH_TEST);

	for (int i = 0; i < 3; i++) {
		switch (i)
		{
		case 0:
			color = Vector3D(1, 0, 0);
			break;
		case 1:
			color = Vector3D(0, 1, 0);
			rotate = MxFactory::rotation4(Vector3D(0, 0, 1), 90 * sign) * rotate;
			break;
		case 2:
			color = Vector3D(0, 0, 1);
			rotate = MxFactory::rotation4(Vector3D(1, 0, 0), 90 * sign) * rotate;
			break;
		}

		model = translate * rotate * scale;

		glStencilFunc(GL_ALWAYS, 0xFF - i, 0xFF); // FF -> y, FF - 1 -> z, FF - 2 -> x
		glStencilOp(GL_ZERO, GL_KEEP, GL_REPLACE);

		shader->bind();

		shader->setUniformVec3("u_AlbedoColor", color);
		shader->setUniformMat4("ModelMatrix", model);
		mesh->draw();
		shader->unbind();		
	}

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDepthMask(GL_TRUE);
	glDepthRange(0.0, 1.0);
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
	this->dist = cam->eye.length();
}

void SceneGraph::saveCurr()
{
	nameMap[current->name] = current;
}

void SceneGraph::setOutline(Material* mat) {
	outline = mat;
}

void SceneGraph::setGrid(Material* mat, Mesh* mesh, TransformInfo info)
{
	grid = new SceneNode();
	grid->name = "grid";
	grid->mesh = mesh;
	grid->transform = info.transform;
	grid->inverse = info.inverse; // Hack, because only useful for normal matrix

	grid->material = mat;
}

void SceneGraph::setHud(Material* mat, Mesh* mesh)
{
	hud = new SceneNode();
	hud->name = "hud";
	hud->mesh = mesh;
	hud->material = mat;
}

void SceneGraph::setGizmo(Material* mat, Mesh* mesh)
{
	gizmo = new SceneNode();
	gizmo->material = mat;
	gizmo->mesh = mesh;
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
	Matrix3 invTransView = cam->invView.decrease().transpose();

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
			curr->material->update(info.transform, invTransView * transpinv); 

			glStencilFunc(GL_ALWAYS, curr->id, 0xFF);
			glStencilOp(GL_ZERO, GL_KEEP, GL_REPLACE);

			curr->mesh->draw();

			curr->material->unbind();

			// Draw Outline
			if (selected == curr->id) 
			{
				outline->bind();
				outline->update(info.transform, invTransView * transpinv);
				glCullFace(GL_FRONT);
				curr->mesh->draw();
				glCullFace(GL_BACK);
				outline->unbind();
			}
		}
	}

	if (selected != 0) {
		drawGizmos();
	}

	glDisable(GL_STENCIL_TEST);


	// draw grid
	glDisable(GL_CULL_FACE);

	grid->material->bind();
	grid->material->update(grid->transform, invTransView * grid->inverse.transpose().decrease());
	grid->mesh->draw();
	grid->material->unbind();

	//draw HUD
	glClear(GL_DEPTH_BUFFER_BIT);
	hud->material->bind();
	hud->mesh->draw();
	hud->material->unbind();

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
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

void SceneGraph::changeParent(unsigned int newChild)
{
	if (selected == 0) return;
	if (selected == newChild) return;

	if (newChild == 0) changeParent(idMap[selected]->name, "root");
	else changeParent(idMap[newChild]->name, idMap[selected]->name);
}

void SceneGraph::changeParent(std::string node, std::string newParent)
{
	if (node == newParent) return;

	SceneNode* changed = nameMap[node];
	SceneNode* origParentNode = changed->parent;
	SceneNode* newParentNode = nameMap[newParent];

	if (origParentNode == newParentNode) {
		std::cout << "same" << std::endl;
		return;
	}

	if (changed == newParentNode->parent) {
		std::cout << "parent-child switch" << std::endl;
		return;
	}
	
	TransformInfo newParentInfo = newParentNode->getTransformInfo();
	std::cout << "new: " << newParentInfo.transform << std::endl;

	setTransforms(node, { changed->getTransformInfo(), newParentInfo.invert() });

	origParentNode->children.erase(std::remove(origParentNode->children.begin(), origParentNode->children.end(), changed), origParentNode->children.end());

	changed->parent = newParentNode;
	newParentNode->children.push_back(changed);

	changed->parentInfo = newParentInfo;
}
void SceneGraph::changeMaterial(std::string objname, Material* material) {
	SceneNode* object = nameMap[objname];
	object->material = material;
}

void SceneGraph::removeObject(std::string objName)
{
	if (nameMap.find(objName) == nameMap.end()) return;

	SceneNode* node = nameMap[objName];
	for (auto child : node->children) {
		changeParent(child->name, "root");
	}

	nameMap.erase(objName);

	SceneNode* parent = node->parent;
	parent->children.erase(std::remove(parent->children.begin(), parent->children.end(), node), parent->children.end());

	node->children = std::vector<SceneNode*>();
	node->parent = nullptr;
	node->material = nullptr;
	node->outline = nullptr;
	delete node;
	selected = 0;
}

void SceneGraph::serializeScene(Camera* cam, Manager* man, const std::string& filepath) {
	SceneSerializer ss = SceneSerializer(cam, man, root);
	ss.serialize(filepath);
}

void SceneGraph::loadScene(const std::string& filepath) {
	SceneSerializer ss = SceneSerializer();
	ss.deserialize(filepath);
}
