#include "..\HeaderFiles\matrix.h"

Matrix2 Matrix2::operator=(const Matrix2& m)
{
	return Matrix2();
}

Matrix2 Matrix2::operator+(const Matrix2& m)
{
	return Matrix2(mat[0] + m.mat[0], mat[1] + m.mat[1], mat[2] + m.mat[2], mat[3] + m.mat[3]);
}

Matrix2& Matrix2::operator+=(const Matrix2& m)
{
	mat[0] += m.mat[0]; mat[1] += m.mat[1]; mat[2] += m.mat[2]; mat[3] += m.mat[3];
	return *this;
}

Matrix2 Matrix2::operator-(const Matrix2& m)
{
	return Matrix2(mat[0] - m.mat[0], mat[1] - m.mat[1], mat[2] - m.mat[2], mat[3] - m.mat[3]);
}

Matrix2& Matrix2::operator-=(const Matrix2& m)
{
	mat[0] -= m.mat[0]; mat[1] -= m.mat[1]; mat[2] -= m.mat[2]; mat[3] -= m.mat[3];
	return *this;
}

Matrix2 Matrix2::operator*(const Matrix2& m)
{
	return Matrix2(
		mat[0] * m.mat[0] + mat[2] * m.mat[1],
		mat[1] * m.mat[0] + mat[3] * m.mat[1],
		mat[0] * m.mat[2] + mat[2] * m.mat[3],
		mat[1] * m.mat[2] + mat[3] * m.mat[3]
	);
}

Matrix2 Matrix2::operator*=(const Matrix2& m)
{
	mat[0] = mat[0] * m.mat[0] + mat[2] * m.mat[1];
	mat[1] = mat[1] * m.mat[0] + mat[3] * m.mat[1];
	mat[2] = mat[0] * m.mat[2] + mat[2] * m.mat[3];
	mat[3] = mat[1] * m.mat[2] + mat[3] * m.mat[3];
	return *this;
}

bool Matrix2::operator==(const Matrix2& m)
{
	return false;
}

bool Matrix2::operator!=(const Matrix2& m)
{
	return false;
}

Matrix2 Matrix2::operator*(const float f)
{
	return Matrix2();
}

Matrix2& Matrix2::operator*=(const float m)
{
	// TODO: insert return statement here
	return *this;
}

Matrix2 Matrix2::operator/(const float f)
{
	return Matrix2();
}

Matrix2& Matrix2::operator/=(const float m)
{
	// TODO: insert return statement here
	return *this;
}

Matrix2 Matrix2::operator+(float f)
{
	return Matrix2();
}

Matrix2& Matrix2::operator+=(const float m)
{
	// TODO: insert return statement here
	return *this;
}

Matrix2 Matrix2::operator-(float f)
{
	return Matrix2();
}

Matrix2& Matrix2::operator-=(const float m)
{
	// TODO: insert return statement here
	return *this;
}

Matrix2 operator*(const float f, const Matrix2& m)
{
	return Matrix2();
}

Matrix2 operator/(const float f, const Matrix2& m)
{
	return Matrix2();
}

Matrix2 operator+(float f, const Matrix2& m)
{
	return Matrix2();
}

Matrix2 operator-(float f, const Matrix2& m)
{
	return Matrix2();
}
