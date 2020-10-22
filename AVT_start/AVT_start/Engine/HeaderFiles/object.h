#pragma once

#include "vector.h"
#include "matrix.h"
#include "mxfactory.h"
#include <vector>
#include <GL/glew.h>

class Object {
public:
	GLuint VaoId, VboId[2];
	vector<Vector4D> positions;
	vector<Vector4D> vertexColors;
	Matrix4 transformations;

	Object() {
		transformations = MxFactory::identity4();
	}

	void rotateAroundAxis(double ax, double ay, double az, double angle);
	void translate(double ax, double ay, double az);
	void scale(double ax, double ay, double az);
	void addVertex(double posx, double posy, double posz, double r, double g, double b, double a);
	//GLfloat* getVertexInfo();

	void initObject();
	void drawObject(GLuint ProgramId);
};