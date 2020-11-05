#pragma once

#include "vector.h"
#include "matrix.h"
#include "mxfactory.h"
#include <vector>
#include <GL/glew.h>

#define POSITIONS 0
#define COLORS 1

class Object {
public:
	GLuint VaoId, VboId[2];
	vector<Vector4D> positions;
	vector<Vector4D> vertexColors;
	Matrix4 transformations;
	Matrix4 initTransformations;
	vector<GLushort> indices;

	Object() {
		transformations = MxFactory::identity4();
		initTransformations = transformations;
	}

	void rotateAroundAxis(Vector3D axis, double angle);
	void translate(Vector3D translateVec);
	void scale(Vector3D scaleVec);
	void addVertex(double posx, double posy, double posz, double r, double g, double b, double a);
	void addTriangle(GLushort v1, GLushort v2, GLushort v3);
	void deleteObject();
	//GLfloat* getVertexInfo();

	void initObject();
	void drawObject(GLuint ProgramId);

	void saveInitTransform();
	void resetTransform();
	void setTransform(Matrix4 transform);
};