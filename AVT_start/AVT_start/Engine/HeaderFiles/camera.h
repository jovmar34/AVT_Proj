#pragma once

#define _USE_MATH_DEFINES

#include "vector.h"
#include "matrix.h"

const GLuint UBO_BP = 0;

enum class CameraProj {
	None, Parallel, Perspective
};

enum class Working {
	On, Off
};

class Camera {
public:
	Matrix4 view, projection, invView;
	Vector3D eye, center, up;
	Vector3D v, s, u;
	bool change = true;
	GLuint VboId = 0, UboId = 0;
	CameraProj projType = CameraProj::None;
	Working state = Working::Off;

	Camera() { };
	Camera(Vector3D _eye, Vector3D _center, Vector3D _up);

	void parallelProjection(double l, double r, double b,double t, double n, double f);
	void perspectiveProjection(double fovy, double aspect, double near, double far);
	void move(Vector3D dir, double speed);
	void look(double angle_h, double angle_v);
	void updateView();
	void toggle();

	void drawCamera();
};
