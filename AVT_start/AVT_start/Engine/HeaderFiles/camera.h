#pragma once

#include "matrix.h"

class Camera {
public:
	Vector3D eye, center, up;
	Matrix4 view, projection;
	bool change = true;
	GLuint VboId;

	Camera() { };
	Camera(Vector3D _eye, Vector3D _center, Vector3D _up) : 
		eye(_eye), center(_center), up(_up) { };

	void setupCamera();
	void parallelProjection(double l, double r, double b,double t, double n, double f);
	void updateView();

	void drawCamera(GLuint ProgramId);
};