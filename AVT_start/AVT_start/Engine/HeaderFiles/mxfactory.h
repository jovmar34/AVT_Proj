#ifndef MXFACORY_H
#define MXFACORY_H

#include "../HeaderFiles/matrix.h"

class MxFactory {
public:
	// Matrix2: identity
	Matrix2 identity2();

	// Matrix3: identity, dual

	// Matrix4: identity, scaling, translation, rotation (Rodrigues)
};

#endif
