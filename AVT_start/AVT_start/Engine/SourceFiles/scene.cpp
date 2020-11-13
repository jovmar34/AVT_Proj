#include "..\HeaderFiles\scene.h"

Scene::Scene(Camera* _cam) 
	: cam(_cam)
{
}

Scene::~Scene()
{
}

void Scene::addObject(Object& obj)
{
	objects.push_back(obj);
}

void Scene::init(GLuint ProgramId)
{

	cam->setupCamera(ProgramId);

	glGenVertexArrays(1, &VaoId);
	glBindVertexArray(VaoId);

	objects[0].initObject(ProgramId);

	glBindVertexArray(0);
}

void Scene::draw()
{
	cam->drawCamera();

	glBindVertexArray(VaoId);

	objects[0].drawObject();

	glBindVertexArray(0);
	
}
