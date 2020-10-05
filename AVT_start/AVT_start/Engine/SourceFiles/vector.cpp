#include "../HeaderFiles/vector.h"
#include <math.h>

// ================================== VECTOR 2D =====================================


Vector2D::Vector2D(float a_x, float a_y) : x(a_x), y(a_y) { }

float Vector2D::length()
{
	return sqrt(quadrance());
}


float Vector2D::quadrance()
{
	return x * x + y * y;
}


// --------------------------------------------------------------------- copy constructor
Vector2D::Vector2D(const Vector2D& v)
{
	x = v.x; y = v.y;
}

// --------------------------------------------------------------------- assignment operator
Vector2D Vector2D::operator= (const Vector2D& other) {
	if (this == &other)
		return (*this);
	x = other.x;
	y = other.y;
	return (*this);
}

Vector2D Vector2D::operator+(const  Vector2D& v)
{
	return Vector2D(x + v.x, y + v.y);
}


Vector2D Vector2D::operator-(const Vector2D& v)
{
	return Vector2D(x - v.x, y - v.y);
}


Vector2D Vector2D::operator*(float f)
{
	return Vector2D(x * f, y * f);
}

float Vector2D::operator*(const  Vector2D& v)
{
	return x * v.x + y * v.y;
}

Vector2D Vector2D::operator/(float f)
{
	return Vector2D(x / f, y / f);
}

Vector2D& Vector2D::normalize()
{
	float l = 1.0 / this->length();
	x *= l; y *= l;
	return *this;
}

Vector2D& Vector2D::operator-=(const Vector2D& v)
{
	x -= v.x; y -= v.y; return *this;
}

Vector2D& Vector2D::operator+=(const Vector2D& v)
{
	x += v.x; y += v.y; return *this;
}

// TODO: apply/support slight error (1E-5)
bool Vector2D::operator==(const Vector2D& v)
{
	if (this == &v) return true;
	return (x == v.x && y == v.y);
}

// TODO: apply/support slight error (1E-5)
bool Vector2D::operator!=(const Vector2D& v)
{
	return !(*this == v);
}


Vector2D& Vector2D::operator-=(const float v)
{
	x -= v; y -= v; return *this;
}

Vector2D& Vector2D::operator+=(const float v)
{
	x += v; y += v; return *this;
}

Vector2D& Vector2D::operator*=(const float v)
{
	x *= v; y *= v; return *this;
}

Vector2D& Vector2D::operator/=(const float v)
{
	x /= v; y /= v; return *this;
}

// ================================== VECTOR 3D =====================================

Vector3D::Vector3D(float a_x, float a_y, float a_z) : x(a_x), y(a_y), z(a_z) { }

float Vector3D::length()
{
	return sqrt(quadrance());
}


float Vector3D::quadrance()
{
	return x * x + y * y + z * z;
}


Vector3D::Vector3D(const Vector3D& v)
{
	x = v.x; y = v.y; z = v.z;
}

Vector3D Vector3D::operator= (const Vector3D& other) {
	if (this == &other)
		return (*this);
	x = other.x;
	y = other.y;
	z = other.z;
	return (*this);
}

Vector3D Vector3D::operator+(const  Vector3D& v)
{
	return Vector3D(x + v.x, y + v.y, z + v.z);
}


Vector3D Vector3D::operator-(const Vector3D& v)
{
	return Vector3D(x - v.x, y - v.y, z - v.z);
}


Vector3D Vector3D::operator*(float f)
{
	return Vector3D(x * f, y * f, z * f);
}

float Vector3D::operator*(const  Vector3D& v)
{
	return x * v.x + y * v.y + z * v.z;
}

Vector3D Vector3D::operator/(float f)
{
	return Vector3D(x / f, y / f, z / f);
}

Vector3D& Vector3D::normalize()
{
	float l = 1.0 / this->length();
	x *= l; y *= l; z *= l;
	return *this;
}

Vector3D& Vector3D::operator-=(const Vector3D& v)
{
	x -= v.x; y -= v.y; z -= v.z; return *this;
}

Vector3D& Vector3D::operator+=(const Vector3D& v)
{
	x += v.x; y += v.y; z += v.z; return *this;
}

// TODO: apply/support slight error (1E-5)
bool Vector3D::operator==(const Vector3D& v)
{
	if (this == &v) return true;
	return (x == v.x && y == v.y && z == v.z);
}

// TODO: apply/support slight error (1E-5)
bool Vector3D::operator!=(const Vector3D& v)
{
	return !(*this == v);
}


Vector3D& Vector3D::operator-=(const float v)
{
	x -= v; y -= v; z -= v; return *this;
}

Vector3D& Vector3D::operator+=(const float v)
{
	x += v; y += v; z += v; return *this;
}

Vector3D& Vector3D::operator*=(const float v)
{
	x *= v; y *= v; z *= z; return *this;
}

Vector3D& Vector3D::operator/=(const float v)
{
	x /= v; y /= v; z /= v; return *this;
}



Vector3D Vector3D::operator%(const Vector3D& v)
{
	float sX = y * v.z - z * v.y;
	float sY = z * v.x - x * v.z;
	float sZ = x * v.y - y * v.x;

	return Vector3D(sX, sY, sZ);
}

// ================================================

// ================================== VECTOR 3D =====================================

Vector4D::Vector4D(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) { }

float Vector4D::length()
{
	return sqrt(quadrance());
}


float Vector4D::quadrance()
{
	return x * x + y * y + z * z + w * w;
}


Vector4D::Vector4D(const Vector4D& v)
{
	x = v.x; y = v.y; z = v.z; w = v.w;
}

Vector4D Vector4D::operator= (const Vector4D& other) {
	if (this == &other)
		return (*this);
	x = other.x;
	y = other.y;
	z = other.z;
	w = other.w;
	return (*this);
}

Vector4D Vector4D::operator+(const  Vector4D& v)
{
	return Vector4D(x + v.x, y + v.y, z + v.z, w + v.w);
}


Vector4D Vector4D::operator-(const Vector4D& v)
{
	return Vector4D(x - v.x, y - v.y, z - v.z, w - v.w);
}


Vector4D Vector4D::operator*(float f)
{
	return Vector4D(x * f, y * f, z * f, w * f);
}

float Vector4D::operator*(const  Vector4D& v)
{
	return x * v.x + y * v.y + z * v.z + w * v.w;
}

Vector4D Vector4D::operator/(float f)
{
	return Vector4D(x / f, y / f, z / f, w / f);
}

Vector4D& Vector4D::normalize()
{
	float l = 1.0 / this->length();
	x *= l; y *= l; z *= l; w *= l;
	return *this;
}

Vector4D& Vector4D::operator-=(const Vector4D& v)
{
	x -= v.x; y -= v.y; z -= v.z; w -= v.w; return *this;
}

Vector4D& Vector4D::operator+=(const Vector4D& v)
{
	x += v.x; y += v.y; z += v.z; w += v.w; return *this;
}

// TODO: apply/support slight error (1E-5)
bool Vector4D::operator==(const Vector4D& v)
{
	if (this == &v) return true;
	return (x == v.x && y == v.y && z == v.z && w == v.w);
}

// TODO: apply/support slight error (1E-5)
bool Vector4D::operator!=(const Vector4D& v)
{
	return !(*this == v);
}


Vector4D& Vector4D::operator-=(const float v)
{
	x -= v; y -= v; z -= v; w -= v; return *this;
}

Vector4D& Vector4D::operator+=(const float v)
{
	x += v; y += v; z += v; w += v; return *this;
}

Vector4D& Vector4D::operator*=(const float v)
{
	x *= v; y *= v; z *= z; w *= v; return *this;
}

Vector4D& Vector4D::operator/=(const float v)
{
	x /= v; y /= v; z /= v; w /= v; return *this;
}

// ================================================