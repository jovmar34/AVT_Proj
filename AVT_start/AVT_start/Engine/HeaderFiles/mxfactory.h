#pragma once

#define _USE_MATH_DEFINES

#include "matrix.h"
#include <cmath>

class MxFactory {
public:
	// Matrix2: identity
	static Matrix2 identity2();

	// Matrix3: identity, dual
	static Matrix3 identity3();
	static Matrix3 dual(double ax, double ay, double az);
	static Matrix3 squaredual(double ax, double ay, double az);

	// Matrix4: identity, scaling, translation, rotation (Rodrigues)
	static Matrix4 identity4();
	static Matrix4 scaling4(Vector3D scaleVec);
	static Matrix4 translation4(Vector3D translateVec);
	static Matrix4 rotation4(Vector3D axis, double theta);
	static Matrix3 rotation3(Vector3D axis, double theta);
	static Matrix4 invscaling4(Vector3D scaleVec);
	static Matrix4 invtranslation4(Vector3D translateVec);
	static Matrix4 invrotation4(Vector3D axis, double theta);
	static Matrix3 invrotation3(Vector3D axis, double theta);
};