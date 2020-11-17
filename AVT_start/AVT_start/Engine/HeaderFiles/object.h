#pragma once

#include "vector.h"
#include "matrix.h"
#include "mxfactory.h"
#include <vector>
#include <GL/glew.h>
#include "vertexBuffer.h"
#include "indexBuffer.h"
#include "mesh.h"

class Object {
public:
	Mesh mesh;
	GLuint VaoId;
	Matrix4 transform;
	Matrix4 initTransform;
	float m_zbuf = 0.0f;
	bool m_fake = false;

	Object(Mesh _mesh): mesh(_mesh) {
		transform = MxFactory::identity4();
		initTransform = transform;
	}

	~Object();

	void rotateAroundAxis(Vector3D axis, double angle);
	void translate(Vector3D translateVec);
	void scale(Vector3D scaleVec);

	void initObject(float zbuf, bool fake);
	void drawObject(GLuint ProgramId);

	void saveInitTransform();
	void resetTransform();
	void setTransform(Matrix4 _transform);
};