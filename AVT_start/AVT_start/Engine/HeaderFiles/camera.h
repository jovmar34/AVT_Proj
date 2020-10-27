#pragma once

#define _USE_MATH_DEFINES

#include "matrix.h"

const GLuint UBO_BP = 0;

enum class CameraProj {
	None, Parallel, Perspective
};

class Camera {
public:
	Matrix4 view, projection;
	Vector3D eye, center, up;
	Vector3D v, s, u;
	bool change = true;
	GLuint VboId, UboId;
	CameraProj projType;

	Camera() { };
	Camera(Vector3D _eye, Vector3D _center, Vector3D _up);

	void setupCamera(GLuint ProgramId);
	void parallelProjection(double l, double r, double b,double t, double n, double f);
	void perspectiveProjection(double fovy, double aspect, double near, double far);
	void move(Vector3D dir, double speed);
	void look(double angle_h);
	void updateView();

	void drawCamera(GLuint ProgramId);
};
