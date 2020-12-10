#pragma once

#include "vector.h"
#include "matrix.h"
#include "mxfactory.h"
#include <vector>
#include <GL/glew.h>
#include "vertexBuffer.h"
#include "indexBuffer.h"
#include "objLoader.h"
#include "vertexArray.h"

#define POSITIONS 0
#define UVCOORDS 1
#define NORMALS 2

class Mesh {
public:
	VertexArray* va;
	LoaderInfo vertices;
	VertexBuffer *posbuf, *uvbuf, *normbuf;
	IndexBuffer* indbuf;

	Mesh(std::string path);

	~Mesh();

	void init();
	void draw();
};