#pragma once

#include "engine.h"
#include <vector>


class Object {
public:
	Mesh mesh;
	GLuint UniformId = 0;
	Matrix4 transform;
	Matrix4 initTransform;

	Object(Mesh _mesh): mesh(_mesh) {
		transform = MxFactory::identity4();
		initTransform = transform;
	}

	~Object();

	void rotateAroundAxis(Vector3D axis, double angle);
	void translate(Vector3D translateVec);
	void scale(Vector3D scaleVec);

	void initObject(GLuint ProgramId);
	void drawObject();

	void saveInitTransform();
	void resetTransform();
	void setTransform(Matrix4 _transform);
};