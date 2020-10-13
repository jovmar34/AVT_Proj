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

class Matrix3 {
public:
	array<float, 9> mat;

	Matrix3() { // default constructor to identity matrix
		mat = { 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f };
	}

	Matrix3(float a11, float a21, float a31, float a12, float a22, float a32, float a13, float a23, float a33) {
		mat = { a11, a21, a31, a12, a22, a32, a13, a23, a33 };
	}

	Matrix3(const Matrix3& other) {
		mat[0] = other.mat[0]; mat[1] = other.mat[1]; mat[2] = other.mat[2];
		mat[3] = other.mat[3]; mat[4] = other.mat[4]; mat[5] = other.mat[5];
		mat[6] = other.mat[6]; mat[7] = other.mat[7]; mat[8] = other.mat[8];
	}

	// Getter
	float& operator() (int row, int col);
	float operator() (int row, int col) const;

	// Vector assignment, addition and subtraction
	Matrix3 operator=		(const Matrix3& m);

	Matrix3 operator+		(const Matrix3& m);
	Matrix3& operator+=	(const Matrix3& m);

	Matrix3 operator-		(const Matrix3& m);
	Matrix3& operator-=	(const Matrix3& m);

	// Multiplication
	Matrix3 operator* (const Matrix3& m);
	Matrix3 operator*= (const Matrix3& m);

	// Comparators
	bool operator==	(const Matrix3& m);
	bool operator!=	(const Matrix3& m);

	// Scalar multiplication
	Matrix3 operator*			(const float f);
	friend Matrix3 operator*	(const float f, const Matrix3& m);
	Matrix3& operator*=		(const float m);

	// Scalar division
	Matrix3 operator/			(const float f);
	friend Matrix3 operator/	(const float f, const Matrix3& m);
	Matrix3& operator/=		(const float m);

	// Scalar addition
	Matrix3 operator+			(float f);
	friend Matrix3 operator+	(float f, const Matrix3& m);
	Matrix3& operator+=		(const float m);

	// Scalar subtraction
	Matrix3 operator-			(float f);
	friend Matrix3 operator-	(float f, const Matrix3& m);
	Matrix3& operator-=		(const float m);

	// Multiplication by Vector
	Vector3D operator* (Vector3D point);

	// Transpose
	Matrix3 transpose();

	// Determinant
	float determinant();

	// Inverse
	Matrix3 inverse();

	// toOpenGl
	std::array<float, 9> toOpenGl() {
		return mat;
	}

	friend inline istream& operator >> (istream& s, Matrix3& m)
	{
		return s >> m.mat[0] >> m.mat[1] >> m.mat[2] >> m.mat[3] >> m.mat[4] >>
			m.mat[5] >> m.mat[6] >> m.mat[7] >> m.mat[8];
	}

	friend inline ostream& operator << (ostream& s, Matrix3& m)
	{
		s << setprecision(4);
		s << "[" << m.mat[0] << " " << m.mat[3] << " " << m.mat[6] << "]\n[" 
			<< m.mat[1] << " " << m.mat[4] << " " << m.mat[7] << "]\n["
			<< m.mat[2] << " " << m.mat[5] << " " << m.mat[8] << "]\n";
		return s;
	}
};


#endif