#pragma once
#include <vector>
#include "engine.h"

class Scene {
private:
	GLuint VaoId;
	Camera *cam;
	vector<Object> objects;
	vector<unsigned int> firsts;
	VertexBuffer* posbuf, * uvbuf, * normbuf;
	IndexBuffer* indbuf;

public:
	Scene(Camera* _cam);
	~Scene();

	void addObject(Object& obj);
	void init(GLuint ProgramId);
	void draw();
};