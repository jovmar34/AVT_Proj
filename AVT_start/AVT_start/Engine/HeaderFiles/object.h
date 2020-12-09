#pragma once

#include "vector.h"
#include "matrix.h"
#include "mxfactory.h"
#include <vector>
#include <GL/glew.h>
#include "vertexBuffer.h"
#include "indexBuffer.h"
#include "mesh.h"
#include "vertexArray.h"

class Object {
public:
	Mesh mesh;
	VertexArray* va;
	GLuint VaoId, ProgramId;
	Matrix4 transform;
	Matrix4 initTransform;
	float m_zbuf;
	bool m_fake;

	Object(Mesh _mesh, float zbuf, int fake);

	~Object();

	void rotateAroundAxis(Vector3D axis, double angle);
	void translate(Vector3D translateVec);
	void scale(Vector3D scaleVec);

	void initObject(GLuint ProgId);
	void drawObject(Matrix4& transf);

	void saveInitTransform();
	void resetTransform();
	void setTransform(Matrix4 _transform);
	Vector3D getPosition();
	Vector3D getBasePosition();
};