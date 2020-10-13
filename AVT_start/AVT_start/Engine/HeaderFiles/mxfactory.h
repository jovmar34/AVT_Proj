#ifndef MXFACORY_H
#define MXFACORY_H

#include "../HeaderFiles/matrix.h"

class MxFactory {
public:
	// Matrix2: identity
	Matrix2 identity2();

	// Matrix3: identity, dual
	Matrix3 identity3();
	Matrix3 dual(float ax, float ay, float az);
	Matrix3 squaredual(float ax, float ay, float az);

	// Matrix4: identity, scaling, translation, rotation (Rodrigues)
	Matrix4 identity4();
	Matrix4 scaling4(float sx, float sy, float sz);
	Matrix4 translation4(float tx, float ty, float tz);
	Matrix4 rotation4(float rx, float ry, float rz, float theta);
	Matrix4 invscaling4(float sx, float sy, float sz);
	Matrix4 invtranslation4(float tx, float ty, float tz);
	Matrix4 invrotation4(float rx, float ry, float rz, float theta);

};

#endif
