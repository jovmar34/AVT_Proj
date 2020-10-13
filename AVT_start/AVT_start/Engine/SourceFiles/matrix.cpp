#include "..\HeaderFiles\matrix.h"

// ================================== MATRIX 2D =====================================

float& Matrix2::operator()(int row, int col)
{
	if (row >= 2 || col >= 2)
		throw "Matrix subscript out of bounds";
	return mat[row + col * 2];
}

float Matrix2::operator()(int row, int col) const
{
	if (row >= 2 || col >= 2)
		throw "Matrix subscript out of bounds";
	return mat[row + col*2];
}

Matrix2 Matrix2::operator=(const Matrix2& m)
{
	if (this == &m) return (*this);
	mat[0] = m.mat[0];	mat[1] = m.mat[1];
	mat[2] = m.mat[2];	mat[3] = m.mat[3];
	return (*this);
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
	if (this == &m) return true;
	return (mat[0] == m.mat[0] && mat[1] == m.mat[1] &&
		mat[2] == m.mat[2] && mat[3] == m.mat[3]);
}

bool Matrix2::operator!=(const Matrix2& m)
{
	return !(*this == m);
}

Matrix2 Matrix2::operator*(const float f)
{
	return Matrix2(mat[0]*f, mat[1]*f, mat[2] * f, mat[3] * f);
}

Matrix2& Matrix2::operator*=(const float f)
{
	mat[0] *= f; mat[1] *= f; mat[2] *= f; mat[3] *= f;
	return *this;
}

Matrix2 Matrix2::operator/(const float f)
{
	return Matrix2(mat[0] / f, mat[1] / f, mat[2] / f, mat[3] / f);
}

Matrix2& Matrix2::operator/=(const float f)
{
	mat[0] /= f; mat[1] /= f; mat[2] /= f; mat[3] /= f;
	return *this;
}

Matrix2 Matrix2::operator+(float f)
{
	return Matrix2(mat[0] + f, mat[1] + f, mat[2] + f, mat[3] + f);
}

Matrix2& Matrix2::operator+=(const float f)
{
	mat[0] += f; mat[1] += f; mat[2] += f; mat[3] += f;
	return *this;
}

Matrix2 Matrix2::operator-(float f)
{
	return Matrix2(mat[0] - f, mat[1] - f, mat[2] - f, mat[3] - f);
}

Matrix2& Matrix2::operator-=(const float f)
{
	mat[0] -= f; mat[1] -= f; mat[2] -= f; mat[3] -= f;
	return *this;
}

Vector2D Matrix2::operator*(Vector2D point)
{
	return Vector2D(mat[0]*point.x + mat[2] * point.y,
		mat[1] * point.x + mat[3] * point.y);
}

Matrix2 Matrix2::transpose()
{
	return Matrix2(mat[0], mat[2], mat[1], mat[3]);
}

float Matrix2::determinant()
{
	return (mat[0] * mat[3] - mat[2] * mat[1]); // ab - bc
}

Matrix2 Matrix2::inverse()
{
	float det = determinant();
	if (det == 0) {
		throw "non invertible matrix";
	}
	Matrix2 inv(mat[3], -mat[1], -mat[2], mat[0]);
	return inv / det;
}

Matrix2 operator*(const float f, const Matrix2& m)
{
	return Matrix2(f * m.mat[0], f * m.mat[1], f * m.mat[2], f * m.mat[3]);
}

Matrix2 operator/(const float f, const Matrix2& m)
{
	return Matrix2(f / m.mat[0], f / m.mat[1], f / m.mat[2], f / m.mat[3]);
}

Matrix2 operator+(float f, const Matrix2& m)
{
	return Matrix2(f + m.mat[0], f + m.mat[1], f + m.mat[2], f + m.mat[3]);
}

Matrix2 operator-(float f, const Matrix2& m)
{
	return Matrix2(f - m.mat[0], f - m.mat[1], f - m.mat[2], f - m.mat[3]);
}

// ================================== MATRIX 4D =====================================

float& Matrix4::operator()(int row, int col)
{
	if (row >= 4 || col >= 4)
		throw "Matrix subscript out of bounds";
	return mat[row + (col * 4)];
}

float Matrix4::operator()(int row, int col) const
{
	if (row >= 4 || col >= 4)
		throw "Matrix subscript out of bounds";
	return mat[row + (col * 4)];
}

Matrix4 Matrix4::operator=(const Matrix4& m)
{
	if (this == &m) return (*this);
	std::copy(std::begin(m.mat), std::end(m.mat), std::begin(mat));
	return (*this);
}

Matrix4 Matrix4::operator+(const Matrix4& m)
{
	Matrix4 new_mat = Matrix4();
	for (int i = 0; i < 16; i++)
	{
		new_mat.mat[i] = mat[i] + m.mat[i];
	}
	return new_mat;
}

Matrix4& Matrix4::operator+=(const Matrix4& m)
{
	for (int i = 0; i < 16; i++)
	{
		mat[i] += m.mat[i];
	}
	return *this;
}

Matrix4 Matrix4::operator-(const Matrix4& m)
{
	Matrix4 new_mat = Matrix4();
	for (int i = 0; i < 16; i++)
	{
		new_mat.mat[i] = mat[i] - m.mat[i];
	}
	return new_mat;

}

Matrix4& Matrix4::operator-=(const Matrix4& m)
{
	for (int i = 0; i < 16; i++)
	{
		mat[i] -= m.mat[i];
	}
	return *this;
}


Matrix4 Matrix4::operator*(const Matrix4& m)
{
	int ind0, ind1, ind2;
	Matrix4 new_mat = Matrix4();

	for (int row = 0; row < 4; row++) {
		
		for (int col = 0; col < 4; col++) {

			ind0 = row + (col * 4);
			for (int k = 0; k < 4; k++){

				ind1 = row + (k * 4);
				ind2 = k + (col * 4);
				new_mat.mat[ind0] += mat[ind1] * m.mat[ind2];
			}
			std::cout << " -> " << new_mat.mat[ind0] << std::endl;
		}
	}

	return new_mat;
}

Matrix4 Matrix4::operator*=(const Matrix4& m)
{
	*this = *this * m;	
	return *this;
}
