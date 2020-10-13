#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <cmath>
#include <cfloat>
#include <array>
#include <iomanip> // setprecision(x)
#include "../HeaderFiles/vector.h"

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

	// Getter
	float& operator() (int row, int col);
	float operator() (int row, int col) const;

	// Vector assignment, addition and subtraction
	Matrix2 operator=		(const Matrix2& m);

	Matrix2 operator+		(const Matrix2& m);
	Matrix2& operator+=		(const Matrix2& m);

	Matrix2 operator-		(const Matrix2& m);
	Matrix2& operator-=		(const Matrix2& m);

	// Multiplication
	Matrix2 operator*	(const Matrix2& m);
	Matrix2 operator*=	(const Matrix2& m);

	// Comparators
	bool operator==		(const Matrix2& m);
	bool operator!=		(const Matrix2& m);

	// Scalar multiplication
	Matrix2 operator*			(const float f);
	friend Matrix2 operator*	(const float f, const Matrix2& m);
	Matrix2& operator*=			(const float m);

	// Scalar division
	Matrix2 operator/			(const float f);
	friend Matrix2 operator/	(const float f, const Matrix2& m);
	Matrix2& operator/=			(const float m);

	// Scalar addition
	Matrix2 operator+			(float f);
	friend Matrix2 operator+	(float f, const Matrix2& m);
	Matrix2& operator+=			(const float m);

	// Scalar subtraction
	Matrix2 operator-			(float f);
	friend Matrix2 operator-	(float f, const Matrix2& m);
	Matrix2& operator-=			(const float m);

	// Multiplication by Vector
	Vector2D operator* (Vector2D point);

	// Transpose
	Matrix2 transpose();

	// Determinant
	float determinant();

	// Inverse
	Matrix2 inverse();

	// toOpenGl
	std::array<float, 4> toOpenGl() {
		return mat;
	}

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




class Matrix4 {
public:
	array<float, 16> mat;

	Matrix4() { // default constructor to identity matrix
		mat = { 1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f, 
				0.0f, 0.0f, 0.0f, 1.0f, };
	}

	Matrix4(float a11, float a12, float a13, float a14, 
			float a21, float a22, float a23, float a24, 
			float a31, float a32, float a33, float a34, 
			float a41, float a42, float a43, float a44) {

		mat = { a11, a21, a31, a41,
				a12, a22, a32, a42,
				a13, a23, a33, a43,
				a14, a24, a34, a44, };
	}

	Matrix4(std::array<float, 16> arr) {

		mat = { arr[0], arr[4], arr[8],  arr[12],
				arr[1], arr[5], arr[9],  arr[13],
				arr[2], arr[6], arr[10], arr[14],
				arr[3], arr[7], arr[11], arr[15], };
	}

	Matrix4(const Matrix4& other) {
		std::copy(std::begin(other.mat), std::end(other.mat), std::begin(mat));
	}

	// Getter
	float& operator() (int row, int col);
	float operator() (int row, int col) const;

	// Vector assignment, addition and subtraction
	Matrix4 operator=		(const Matrix4& m);

	Matrix4 operator+		(const Matrix4& m);
	Matrix4& operator+=		(const Matrix4& m);

	Matrix4 operator-		(const Matrix4& m);
	Matrix4& operator-=		(const Matrix4& m);

	// Multiplication
	Matrix4 operator*		(const Matrix4& m);
	Matrix4 operator*=		(const Matrix4& m);

	// Comparators
	bool operator==			(const Matrix4& m);
	bool operator!=			(const Matrix4& m);

	// Scalar multiplication
	Matrix4 operator*			(const float f);
	friend Matrix4 operator*	(const float f, const Matrix4& m);
	Matrix4& operator*=			(const float m);

	// Scalar division
	Matrix4 operator/			(const float f);
	friend Matrix4 operator/	(const float f, const Matrix4& m);
	Matrix4& operator/=			(const float m);

	// Scalar addition
	Matrix4 operator+			(float f);
	friend Matrix4 operator+	(float f, const Matrix4& m);
	Matrix4& operator+=			(const float m);

	// Scalar subtraction
	Matrix4 operator-			(float f);
	friend Matrix4 operator-	(float f, const Matrix4& m);
	Matrix4& operator-=			(const float m);

	// Multiplication by Vector
	Vector2D operator* (Vector2D point);

	// Transpose
	Matrix4 transpose();

	// Inverse
	Matrix4 inverse();

	// toOpenGl
	std::array<float, 16> toOpenGl() {
		return mat;
	}

	friend inline istream& operator >> (istream& s, Matrix4& m)
	{
		return s	>> m.mat[0]		>> m.mat[4]		>> m.mat[8]		>> m.mat[12]
					>> m.mat[1]		>> m.mat[5]		>> m.mat[9]		>> m.mat[13] 
					>> m.mat[2]		>> m.mat[6]		>> m.mat[10]	>> m.mat[14] 
					>> m.mat[3]		>> m.mat[7]		>> m.mat[11]	>> m.mat[15];
	}

	friend inline ostream& operator << (ostream& s, Matrix4& m)
	{
		s << setprecision(4);
		s << "["	<< m.mat[0] << " " << m.mat[4] << " " << m.mat[8]	<< " " << m.mat[12] << "]\n[" 
					<< m.mat[1] << " " << m.mat[5] << " " << m.mat[9]	<< " " << m.mat[13] << "]\n["
					<< m.mat[2] << " " << m.mat[6] << " " << m.mat[10]	<< " " << m.mat[14] << "]\n["
					<< m.mat[3] << " " << m.mat[7] << " " << m.mat[11]	<< " " << m.mat[15] << "]\n";
		return s;
	}
};

#endif