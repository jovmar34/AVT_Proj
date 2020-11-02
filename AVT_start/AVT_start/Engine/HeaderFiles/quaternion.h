#pragma once

#define _USE_MATH_DEFINES

#include "matrix.h"

class Quaternion {
public:	
	double t, x, y, z;

	Quaternion();
	Quaternion(double _t, double _x, double _y, double _z);
	Quaternion(double theta, Vector4D axis);

	Vector4D toAngleAxis(float& theta);
	double quadrance();
	double norm();
	Quaternion& normalize();
	Quaternion conjugate();
	Quaternion inverse();

	Quaternion operator=(const Quaternion& q1);
	Quaternion operator+(const Quaternion& q1);
	Quaternion operator*(const double s);
	Quaternion operator*(const Quaternion& q1);
	Quaternion operator/(const double s);
	GLfloat* toOpenGLRot();
	Quaternion Lerp(Quaternion& q1, double k);
	Quaternion Slerp(Quaternion& q1, float k);
	bool operator==(const Quaternion& q1);

	void print();
	void printAngleAxis();

};