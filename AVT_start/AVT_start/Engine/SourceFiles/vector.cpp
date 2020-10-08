#include "../HeaderFiles/vector.h"
#include <math.h>

// ================================== VECTOR 2D =====================================


Vector2D::Vector2D(float a_x, float a_y) : x(a_x), y(a_y) { }

Vector2D::Vector2D(const Vector2D& v)
{
	x = v.x; y = v.y;
}

// Vector functions
float Vector2D::length()
{
	return sqrt(quadrance());
}

float Vector2D::quadrance()
{
	return x * x + y * y;
}

Vector2D& Vector2D::normalize()
{
	float l = 1.0 / this->length();
	x *= l; y *= l;
	return *this;
}

// Vector assignment, addition and subtraction
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

Vector2D& Vector2D::operator+=(const Vector2D& v)
{
	x += v.x; y += v.y; return *this;
}

Vector2D Vector2D::operator-(const Vector2D& v)
{
	return Vector2D(x - v.x, y - v.y);
}

Vector2D& Vector2D::operator-=(const Vector2D& v)
{
	x -= v.x; y -= v.y; return *this;
}

// Inner product
float Vector2D::operator*(const  Vector2D& v)
{
	return x * v.x + y * v.y;
}

// Comparators - TODO: apply/support slight error (1E-5)
bool Vector2D::operator==(const Vector2D& v)
{
	if (this == &v) return true;
	return (x == v.x && y == v.y);
}

bool Vector2D::operator!=(const Vector2D& v)
{
	return !(*this == v);
}

// Scalar multiplication
Vector2D Vector2D::operator*(const float f)
{
	return Vector2D(x * f, y * f);
}

Vector2D operator*(const float f, const Vector2D& v) {
	return Vector2D(v.x * f, v.y * f);
}

Vector2D& Vector2D::operator*=(const float v)
{
	x *= v; y *= v; return *this;
}

// Scalar division
Vector2D Vector2D::operator/(const float f)
{
	return Vector2D(x / f, y / f);
}

Vector2D operator/(const float f, const Vector2D& v) {
	return Vector2D(f / v.x, f / v.y);
}

Vector2D& Vector2D::operator/=(const float v)
{
	x /= v; y /= v; return *this;
}

// Scalar addition
Vector2D Vector2D::operator+(const float f)
{
	return Vector2D(x + f, y + f);
}

Vector2D operator+(float f, const Vector2D& v) 
{
	return Vector2D(v.x + f, v.y + f);
}

Vector2D& Vector2D::operator+=(const float v)
{
	x += v; y += v; return *this;
}

// Scalar subtraction
Vector2D Vector2D::operator-(const float f)
{
	return Vector2D(x - f, y - f);
}

Vector2D operator-(float f, const Vector2D& v)
{
	return Vector2D(f - v.x, f - v.y);
}

Vector2D& Vector2D::operator-=(const float v)
{
	x -= v; y -= v; return *this;
}

// Conversion
Vector3D Vector2D::to3D() {
	return Vector3D(x, y, 0);
}

Vector4D Vector2D::to4D() {
	return Vector4D(x, y, 0, 0);
}



// ================================== VECTOR 3D =====================================

Vector3D::Vector3D(float a_x, float a_y, float a_z) : x(a_x), y(a_y), z(a_z) { }

Vector3D::Vector3D(const Vector3D& v)
{
	x = v.x; y = v.y; z = v.z;
}

// Vector functions
float Vector3D::length()
{
	return sqrt(quadrance());
}

float Vector3D::quadrance()
{
	return x * x + y * y + z * z;
}

Vector3D& Vector3D::normalize()
{
	float l = 1.0 / this->length();
	x *= l; y *= l; z *= l;
	return *this;
}

// Vector assignment, addition and subtraction
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

Vector3D& Vector3D::operator+=(const Vector3D& v)
{
	x += v.x; y += v.y; z += v.z; return *this;
}

Vector3D Vector3D::operator-(const Vector3D& v)
{
	return Vector3D(x - v.x, y - v.y, z - v.z);
}

Vector3D& Vector3D::operator-=(const Vector3D& v)
{
	x -= v.x; y -= v.y; z -= v.z; return *this;
}

// Inner and Cross product
float Vector3D::operator*(const  Vector3D& v)
{
	return x * v.x + y * v.y + z * v.z;
}

Vector3D Vector3D::operator%(const Vector3D& v)
{
	float sX = y * v.z - z * v.y;
	float sY = z * v.x - x * v.z;
	float sZ = x * v.y - y * v.x;

	return Vector3D(sX, sY, sZ);
}

// Comparators - TODO: apply/support slight error (1E-5)
bool Vector3D::operator==(const Vector3D& v)
{
	if (this == &v) return true;
	return (x == v.x && y == v.y && z == v.z);
}

bool Vector3D::operator!=(const Vector3D& v)
{
	return !(*this == v);
}

// Scalar multiplication
Vector3D Vector3D::operator*(const float f)
{
	return Vector3D(x * f, y * f, z * f);
}

Vector3D operator*(const float f, const Vector3D& v)
{
	return Vector3D(f * v.x, f * v.y, f * v.z);
}

Vector3D& Vector3D::operator*=(const float v)
{
	x *= v; y *= v; z *= z; return *this;
}

// Scalar division
Vector3D Vector3D::operator/(const float f)
{
	return Vector3D(x / f, y / f, z / f);
}

Vector3D operator/(const float f, const Vector3D& v)
{
	return Vector3D(f / v.x, f / v.y, f / v.z);
}

Vector3D& Vector3D::operator/=(const float v)
{
	x /= v; y /= v; z /= v; return *this;
}

// Scalar addition
Vector3D Vector3D::operator+(const float f)
{
	return Vector3D(x + f, y + f, z + f);
}

Vector3D operator+(const float f, const Vector3D& v)
{
	return Vector3D(f + v.x, f + v.y, f + v.z);
}

Vector3D& Vector3D::operator+=(const float v)
{
	x += v; y += v; z += v; return *this;
}

// Scalar subtraction
Vector3D Vector3D::operator-(const float f)
{
	return Vector3D(x - f, y - f, z - f);
}

Vector3D operator-(const float f, const Vector3D& v)
{
	return Vector3D(f - v.x, f - v.y, f - v.z);
}

Vector3D& Vector3D::operator-=(const float v)
{
	x -= v; y -= v; z -= v; return *this;
}

// Conversion
Vector2D Vector3D::to2D() {
	return Vector2D(x, y);
}

Vector4D Vector3D::to4D() {
	return Vector4D(x, y, z, 0);
}



// ================================== VECTOR 4D =====================================

Vector4D::Vector4D(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) { }

Vector4D::Vector4D(const Vector4D& v)
{
	x = v.x; y = v.y; z = v.z; w = v.w;
}

// Vector functions
float Vector4D::length()
{
	return sqrt(quadrance());
}

float Vector4D::quadrance()
{
	return x * x + y * y + z * z + w * w;
}

Vector4D& Vector4D::normalize()
{
	float l = 1.0 / this->length();
	x *= l; y *= l; z *= l; w *= l;
	return *this;
}

// Vector assignment, addition and subtraction
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

Vector4D& Vector4D::operator+=(const Vector4D& v)
{
	x += v.x; y += v.y; z += v.z; w += v.w; return *this;
}

Vector4D Vector4D::operator-(const Vector4D& v)
{
	return Vector4D(x - v.x, y - v.y, z - v.z, w - v.w);
}

Vector4D& Vector4D::operator-=(const Vector4D& v)
{
	x -= v.x; y -= v.y; z -= v.z; w -= v.w; return *this;
}

// Inner product
float Vector4D::operator*(const  Vector4D& v)
{
	return x * v.x + y * v.y + z * v.z + w * v.w;
}

// Comparators - TODO: apply/support slight error (1E-5)
bool Vector4D::operator==(const Vector4D& v)
{
	if (this == &v) return true;
	return (x == v.x && y == v.y && z == v.z && w == v.w);
}

bool Vector4D::operator!=(const Vector4D& v)
{
	return !(*this == v);
}

// Scalar multiplication
Vector4D Vector4D::operator*(float f)
{
	return Vector4D(x * f, y * f, z * f, w * f);
}

Vector4D operator*(const float f, const Vector4D& v)
{
	return Vector4D(f * v.x, f * v.y, f * v.z, f * v.w);
}

Vector4D& Vector4D::operator*=(const float v)
{
	x *= v; y *= v; z *= z; w *= v; return *this;
}

// Scalar division
Vector4D Vector4D::operator/(float f)
{
	return Vector4D(x / f, y / f, z / f, w / f);
}

Vector4D operator/(const float f, const Vector4D& v)
{
	return Vector4D(f / v.x, f / v.y, f / v.z, f / v.w);
}

Vector4D& Vector4D::operator/=(const float v)
{
	x /= v; y /= v; z /= v; w /= v; return *this;
}

// Scalar addition
Vector4D Vector4D::operator+(float f)
{
	return Vector4D(x + f, y + f, z + f, w + f);
}

Vector4D operator+(const float f, const Vector4D& v)
{
	return Vector4D(f + v.x, f + v.y, f + v.z, f + v.w);
}

Vector4D& Vector4D::operator+=(const float v)
{
	x += v; y += v; z += v; w += v; return *this;
}

// Scalar subtraction
Vector4D Vector4D::operator-(float f)
{
	return Vector4D(x - f, y - f, z - f, w - f);
}

Vector4D operator-(const float f, const Vector4D& v)
{
	return Vector4D(f - v.x, f - v.y, f - v.z, f - v.w);
}

Vector4D& Vector4D::operator-=(const float v)
{
	x -= v; y -= v; z -= v; w -= v; return *this;
}

// Conversion
Vector2D Vector4D::to2D() {
	return Vector2D(x, y);
}

Vector3D Vector4D::to3D() {
	return Vector3D(x, y, z);
}