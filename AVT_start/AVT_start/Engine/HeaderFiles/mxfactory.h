#ifndef MXFACORY_H
#define MXFACORY_H

#define _USE_MATH_DEFINES

#include "../HeaderFiles/matrix.h"
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
	static Matrix4 scaling4(double sx, double sy, double sz);
	static Matrix4 translation4(double tx, double ty, double tz);
	static Matrix4 rotation4(double rx, double ry, double rz, double theta);
	static Matrix4 invscaling4(double sx, double sy, double sz);
	static Matrix4 invtranslation4(double tx, double ty, double tz);
	static Matrix4 invrotation4(double rx, double ry, double rz, double theta);

};

#endif
