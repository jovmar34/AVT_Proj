#pragma once

#include <iostream>
#include <string>
#include <cmath>
#include <cfloat>
#include <array>
#include <iomanip> // setprecision(x)
#include "vector.h"

using namespace std;

class Matrix2;
class Matrix3;
class Matrix4;

/* Internal representation format: Column Major

	| a11 a12 a13 | 
	| a21 a22 a23 | => [a11 a21 a31 a12 a22 a32 a13 a23 a33]
	| a31 a32 a33 |
*/

class Matrix2 {
	public:
	array<double, 4> mat;
	GLfloat data[4] = { 
		0,0,
		0,0,
	};

	Matrix2() { // default constructor to additive identity matrix
		mat = { 0.0f, 0.0f, 
				0.0f, 0.0f };
	}

	Matrix2(double a11, double a12, double a21, double a22) {
		mat = { a11, a21, a12, a22 };
	}

	Matrix2(const Matrix2& other) {
		mat = { other.mat[0], other.mat[1], other.mat[2], other.mat[3] };
	}

	// Getter
	double& operator() (long int row, long int col);
	double operator() (long int row, long int col) const;

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
	bool equals			(const Matrix2& m);

	// Scalar multiplication
	Matrix2 operator*			(const double f);
	friend Matrix2 operator*	(const double f, const Matrix2& m);
	Matrix2& operator*=			(const double m);

	// Scalar division
	Matrix2 operator/			(const double f);
	friend Matrix2 operator/	(const double f, const Matrix2& m);
	Matrix2& operator/=			(const double m);

	// Scalar addition
	Matrix2 operator+			(double f);
	friend Matrix2 operator+	(double f, const Matrix2& m);
	Matrix2& operator+=			(const double m);

	// Scalar subtraction
	Matrix2 operator-			(double f);
	friend Matrix2 operator-	(double f, const Matrix2& m);
	Matrix2& operator-=			(const double m);

	// Multiplication by Vector
	Vector2D operator* (Vector2D point);

	// Transpose
	Matrix2 transpose();

	// Determinant
	double determinant();

	// Inverse
	Matrix2 inverse();

	// toOpenGl
	GLfloat* toOpenGl() {
		for (int i = 0; i < 4; i++) {
			data[i] = (GLfloat) mat[i];
		}
		return data;
	}

	friend inline istream& operator >> (istream& s, Matrix2& m)
	{
		return s >> m.mat[0] >> m.mat[1] >> m.mat[2] >> m.mat[3];
	}

	friend inline ostream& operator << (ostream& s, Matrix2& m)
	{
		s << "[" << m.mat[0] << " " << m.mat[2] << "]\n[" << m.mat[1] << " " << m.mat[3] << "]\n";
		return s;
	}

	static size_t byteSize() {
		return 4 * sizeof(GLfloat);
	}
};

class Matrix3 {
public:
	array<double, 9> mat;
	GLfloat data[9] = {
		0,0,0,
		0,0,0,
		0,0,0,
	};

	Matrix3() { // default constructor to identity matrix
		mat = { 0.0f, 0.0f, 0.0f, 
				0.0f, 0.0f, 0.0f, 
				0.0f, 0.0f, 0.0f };
	}

	Matrix3(double a11, double a12, double a13, double a21, double a22, double a23, double a31, double a32, double a33) {
		mat = { a11, a21, a31, a12, a22, a32, a13, a23, a33 };
	}

	Matrix3(const Matrix3& other) {
		mat = { other.mat[0], other.mat[1], other.mat[2],
			other.mat[3], other.mat[4], other.mat[5],
			other.mat[6], other.mat[7], other.mat[8] };
	}

	Matrix3(const array<double, 9> arr) {
		std::copy(std::begin(arr), std::end(arr), std::begin(mat));
	}

	// Getter
	double& operator() (long int row, long int col);
	double operator() (long int row, long int col) const;

	// Vector assignment, addition and subtraction
	Matrix3 operator=		(const Matrix3& m);

	Matrix3 operator+		(const Matrix3& m);
	Matrix3& operator+=		(const Matrix3& m);

	Matrix3 operator-		(const Matrix3& m);
	Matrix3& operator-=		(const Matrix3& m);

	// Multiplication
	Matrix3 operator*	(const Matrix3& m);
	Matrix3 operator*=	(const Matrix3& m);

	// Comparators
	bool operator==		(const Matrix3& m); // equality with error 1E-5
	bool operator!=		(const Matrix3& m);
	bool equals			(const Matrix3& m); // exact equality

	// Scalar multiplication
	Matrix3 operator*			(const double f);
	friend Matrix3 operator*	(const double f, const Matrix3& m);
	Matrix3& operator*=			(const double m);

	// Scalar division
	Matrix3 operator/			(const double f);
	friend Matrix3 operator/	(const double f, const Matrix3& m);
	Matrix3& operator/=			(const double m);

	// Scalar addition
	Matrix3 operator+			(double f);
	friend Matrix3 operator+	(double f, const Matrix3& m);
	Matrix3& operator+=			(const double m);

	// Scalar subtraction
	Matrix3 operator-			(double f);
	friend Matrix3 operator-	(double f, const Matrix3& m);
	Matrix3& operator-=			(const double m);

	// Multiplication by Vector
	Vector3D operator* (Vector3D point);

	// Transpose
	Matrix3 transpose();

	// Determinant
	double determinant();

	// Inverse
	Matrix3 inverse();

	// Increase dimensions
	Matrix4 increase();

	// toOpenGl
	GLfloat* toOpenGl() {
		for (int i = 0; i < 9; i++) {
			data[i] = (GLfloat) mat[i];
		}
		return data;
	}

	friend inline istream& operator >> (istream& s, Matrix3& m)
	{
		return s >> m.mat[0] >> m.mat[1] >> m.mat[2] >> m.mat[3] >> m.mat[4] >>
			m.mat[5] >> m.mat[6] >> m.mat[7] >> m.mat[8];
	}

	friend inline ostream& operator << (ostream& s, Matrix3& m)
	{
		s << "[" << m.mat[0] << " " << m.mat[3] << " " << m.mat[6] << "]\n[" 
				 << m.mat[1] << " " << m.mat[4] << " " << m.mat[7] << "]\n["
				 << m.mat[2] << " " << m.mat[5] << " " << m.mat[8] << "]\n";
		return s;
	}

	static size_t byteSize() {
		return 9 * sizeof(GLfloat);
	}
};

class Matrix4 {
public:
	array<double, 16> mat;
	GLfloat data[16] = {
		0,0,0,0,
		0,0,0,0,
		0,0,0,0,
		0,0,0,0,
	};

	Matrix4() { // default constructor to identity matrix
		mat = { 0.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 0.0f, };
	}

	Matrix4(double a11, double a12, double a13, double a14,
		double a21, double a22, double a23, double a24,
		double a31, double a32, double a33, double a34,
		double a41, double a42, double a43, double a44) {

		mat = { a11, a21, a31, a41,
				a12, a22, a32, a42,
				a13, a23, a33, a43,
				a14, a24, a34, a44, };
	}

	Matrix4(std::array<double, 16> arr) {

		mat = { arr[0], arr[4], arr[8],  arr[12],
				arr[1], arr[5], arr[9],  arr[13],
				arr[2], arr[6], arr[10], arr[14],
				arr[3], arr[7], arr[11], arr[15], };
	}

	string toString() {
		string res = "\n[";
		int n = 0;
		double sc = 0.01;
		while (n < 16) {
			float digit = (int)(mat[n] / sc) * sc;
			string d = std::to_string(digit);
			d.erase(d.find_last_not_of('0') + 1, std::string::npos);
			if (n >= 4 && n % 4 == 0) {
				res += "[" + d + " ";
			}
			else if (n % 4 == 3) {
				res += d + "]\n";
			}
			else {
				res += d + " ";
			}
			n++;
		}
		return res;
	}

	Matrix4(const Matrix4& other) {
		std::copy(std::begin(other.mat), std::end(other.mat), std::begin(mat));
	}

	// Getter
	double& operator() (long int row, long int col);
	double operator() (long int row, long int col) const;

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
	bool operator==			(const Matrix4& m); // equality with error 1E-5
	bool operator!=			(const Matrix4& m);
	bool equals				(const Matrix4& m); // exact equality

	// Scalar multiplication
	Matrix4 operator*			(const double f);
	friend Matrix4 operator*	(const double f, const Matrix4& m);
	Matrix4& operator*=			(const double m);

	// Scalar division
	Matrix4 operator/			(const double f);
	friend Matrix4 operator/	(const double f, const Matrix4& m);
	Matrix4& operator/=			(const double m);

	// Scalar addition
	Matrix4 operator+			(double f);
	friend Matrix4 operator+	(double f, const Matrix4& m);
	Matrix4& operator+=			(const double m);

	// Scalar subtraction
	Matrix4 operator-			(double f);
	friend Matrix4 operator-	(double f, const Matrix4& m);
	Matrix4& operator-=			(const double m);

	// Multiplication by Vector
	Vector4D operator* (Vector4D point);

	// Transpose
	Matrix4 transpose();

	Matrix3 decrease();

	// toOpenGl
	GLfloat* toOpenGl() {
		for (int i = 0; i < 16; i++) {
			data[i] = (GLfloat) mat[i];
		}
		return data;
	}

	friend inline istream& operator >> (istream& s, Matrix4& m)
	{
		return s >> m.mat[0] >> m.mat[4] >> m.mat[8] >> m.mat[12]
				 >> m.mat[1] >> m.mat[5] >> m.mat[9] >> m.mat[13]
				 >> m.mat[2] >> m.mat[6] >> m.mat[10] >> m.mat[14]
				 >> m.mat[3] >> m.mat[7] >> m.mat[11] >> m.mat[15];
	}

	friend inline ostream& operator << (ostream& s, Matrix4& m)
	{
		s << "[" << m.mat[0] << " " << m.mat[4] << " " << m.mat[8] << " " << m.mat[12] << "]\n["
				 << m.mat[1] << " " << m.mat[5] << " " << m.mat[9] << " " << m.mat[13] << "]\n["
				 << m.mat[2] << " " << m.mat[6] << " " << m.mat[10] << " " << m.mat[14] << "]\n["
				 << m.mat[3] << " " << m.mat[7] << " " << m.mat[11] << " " << m.mat[15] << "]\n";
		return s;
	}

	static size_t byteSize() {
		return 16 * sizeof(GLfloat);
	}
};