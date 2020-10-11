#pragma once
#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <cmath>
#include <cfloat>
#include <array>
#include <iomanip> // setprecision(x)

using namespace std;

class Matrix2;
class Matrix3;
class Matrix4;

/*
	TODO: (Joao) matrizes no formato column major (para estar ja alinhado com o OpenGl

	| a11 a12 a13 | 
	| a21 a22 a23 | => [a11 a21 a31 a12 a22 a32 a13 a23 a33]
	| a31 a32 a33 |

	index(row i, col j) = i + a*j (em matriz a x a) 
*/

class Matrix2 {
	public:
	array<float, 4> mat;

	Matrix2() { // default constructor to identity matrix
		mat = { 1.0f, 0.0f, 0.0f, 1.0f };
	}

	Matrix2(float a11, float a21, float a12, float a22) {
		mat = { a11, a21, a12, a22 };
	}

	Matrix2(const Matrix2& other) {
		mat[0] = other.mat[0]; mat[1] = other.mat[1]; mat[2] = other.mat[2]; mat[3] = other.mat[3];
	}

	// Vector assignment, addition and subtraction
	Matrix2 operator=		(const Matrix2& m);

	Matrix2 operator+		(const Matrix2& m);
	Matrix2& operator+=	(const Matrix2& m);

	Matrix2 operator-		(const Matrix2& m);
	Matrix2& operator-=	(const Matrix2& m);

	// Multiplication
	Matrix2 operator* (const Matrix2& m);
	Matrix2 operator*= (const Matrix2& m);

	// Comparators
	bool operator==	(const Matrix2& m);
	bool operator!=	(const Matrix2& m);

	// Scalar multiplication
	Matrix2 operator*			(const float f);
	friend Matrix2 operator*	(const float f, const Matrix2& m);
	Matrix2& operator*=		(const float m);

	// Scalar division
	Matrix2 operator/			(const float f);
	friend Matrix2 operator/	(const float f, const Matrix2& m);
	Matrix2& operator/=		(const float m);

	// Scalar addition
	Matrix2 operator+			(float f);
	friend Matrix2 operator+	(float f, const Matrix2& m);
	Matrix2& operator+=		(const float m);

	// Scalar subtraction
	Matrix2 operator-			(float f);
	friend Matrix2 operator-	(float f, const Matrix2& m);
	Matrix2& operator-=		(const float m);

	friend inline istream& operator >> (istream& s, Matrix2& m)
	{
		return s >> m.mat[0] >> m.mat[1] >> m.mat[2] >> m.mat[3];
	}

	friend inline ostream& operator << (ostream& s, Matrix2& m)
	{
		s << setprecision(4);
		s << "[" << m.mat[0] << " " << m.mat[2] << "]\n[" << m.mat[1] << " " << m.mat[3] << "]\n";
		return s;
	}
};


#endif