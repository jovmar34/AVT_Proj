#pragma once

#define _USE_MATH_DEFINES

#include "matrix.h"

class Quaternion {
public:
	double t, x, y, z;

	Quaternion();
	Quaternion(double _t, double _x, double _y, double _z);
	Quaternion(double theta, Vector4D axis);

	Vector4D toAngleAxis(double& theta);
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
	Matrix4 rotMat();
	GLfloat* toOpenGLRot();
	Quaternion Lerp(Quaternion& q1, double k);
	Quaternion Slerp(Quaternion& q1, double k);
	bool operator==(const Quaternion& q1);

	friend inline ostream& operator << (ostream& s, Quaternion& q)
	{
		s << "(" << q.t << "," << q.x << "," << q.y << "," << q.z << ")";
		return s;
	}

};