#ifndef MXFACORY_H
#define MXFACORY_H

#define _USE_MATH_DEFINES

#include "../HeaderFiles/matrix.h"
#include <cmath>

class MxFactory {
public:
	// Matrix2: identity
	Matrix2 identity2();

	// Matrix3: identity, dual
	Matrix3 identity3();
	Matrix3 dual(double ax, double ay, double az);
	Matrix3 squaredual(double ax, double ay, double az);

	// Matrix4: identity, scaling, translation, rotation (Rodrigues)
	Matrix4 identity4();
	Matrix4 scaling4(double sx, double sy, double sz);
	Matrix4 translation4(double tx, double ty, double tz);
	Matrix4 rotation4(double rx, double ry, double rz, double theta);
	Matrix4 invscaling4(double sx, double sy, double sz);
	Matrix4 invtranslation4(double tx, double ty, double tz);
	Matrix4 invrotation4(double rx, double ry, double rz, double theta);

};

#endif
