#include "../HeaderFiles/vector.h"
#include <cmath>

// ================================== VECTOR 2D =====================================


Vector2D::Vector2D(double a_x, double a_y) : x(a_x), y(a_y) { }

Vector2D::Vector2D(const Vector2D& v)
{
	x = v.x; y = v.y;
}

// Vector functions
double Vector2D::length()
{
	return sqrt(quadrance());
}

double Vector2D::quadrance()
{
	return x * x + y * y;
}

Vector2D& Vector2D::normalize()
{
	double len = this->length();
	if (len == 0) throw "length = 0, can't normalize";
	double l = 1.0 / len;
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
double Vector2D::operator*(const  Vector2D& v)
{
	return x * v.x + y * v.y;
}

// Comparators - TODO: apply/support slight error (1E-5)
bool Vector2D::operator==(const Vector2D& v)
{
	if (this == &v) return true;
	return (abs(x - v.x) < EQERR && abs(y - v.y) < EQERR);
}

bool Vector2D::operator!=(const Vector2D& v)
{
	return !(*this == v);
}

bool Vector2D::equals(const Vector2D& v)
{
	if (this == &v) return true;
	return (x == v.x && y == v.y);
}

// Scalar multiplication
Vector2D Vector2D::operator*(const double f)
{
	return Vector2D(x * f, y * f);
}

Vector2D operator*(const double f, const Vector2D& v) {
	return Vector2D(v.x * f, v.y * f);
}

Vector2D& Vector2D::operator*=(const double v)
{
	x *= v; y *= v; return *this;
}

// Scalar division
Vector2D Vector2D::operator/(const double f)
{
	return Vector2D(x / f, y / f);
}

Vector2D operator/(const double f, const Vector2D& v) {
	return Vector2D(f / v.x, f / v.y);
}

Vector2D& Vector2D::operator/=(const double v)
{
	x /= v; y /= v; return *this;
}

// Scalar addition
Vector2D Vector2D::operator+(const double f)
{
	return Vector2D(x + f, y + f);
}

Vector2D operator+(double f, const Vector2D& v) 
{
	return Vector2D(v.x + f, v.y + f);
}

Vector2D& Vector2D::operator+=(const double v)
{
	x += v; y += v; return *this;
}

// Scalar subtraction
Vector2D Vector2D::operator-(const double f)
{
	return Vector2D(x - f, y - f);
}

Vector2D operator-(double f, const Vector2D& v)
{
	return Vector2D(f - v.x, f - v.y);
}

Vector2D& Vector2D::operator-=(const double v)
{
	x -= v; y -= v; return *this;
}

// Conversion
Vector3D Vector2D::to3D() {
	return Vector3D(x, y, 0);
}

Vector4D Vector2D::to4D() {
	return Vector4D(x, y, 0, 1);
}



// ================================== VECTOR 3D =====================================

Vector3D::Vector3D(double a_x, double a_y, double a_z) : x(a_x), y(a_y), z(a_z) { }

Vector3D::Vector3D(const Vector3D& v)
{
	x = v.x; y = v.y; z = v.z;
}

// Vector functions
double Vector3D::length()
{
	return sqrt(quadrance());
}

double Vector3D::quadrance()
{
	return x * x + y * y + z * z;
}

Vector3D& Vector3D::normalize()
{
	double len = this->length();
	if (len == 0) throw "length = 0, can't normalize";
	double l = 1 / len;
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
double Vector3D::operator*(const  Vector3D& v)
{
	return x * v.x + y * v.y + z * v.z;
}

Vector3D Vector3D::operator%(const Vector3D& v)
{
	double sX = y * v.z - z * v.y;
	double sY = z * v.x - x * v.z;
	double sZ = x * v.y - y * v.x;

	return Vector3D(sX, sY, sZ);
}

// Comparators - TODO: apply/support slight error (1E-5)
bool Vector3D::operator==(const Vector3D& v)
{
	if (this == &v) return true;
	return (abs(x - v.x) < EQERR && abs(y - v.y) < EQERR && abs(z - v.z) < EQERR);
}

bool Vector3D::operator!=(const Vector3D& v)
{
	return !(*this == v);
}

bool Vector3D::equals(const Vector3D& v)
{
	if (this == &v) return true;
	return (x == v.x && y == v.y && z == v.z);
}

// Scalar multiplication
Vector3D Vector3D::operator*(const double f)
{
	return Vector3D(x * f, y * f, z * f);
}

Vector3D operator*(const double f, const Vector3D& v)
{
	return Vector3D(f * v.x, f * v.y, f * v.z);
}

Vector3D& Vector3D::operator*=(const double v)
{
	x *= v; y *= v; z *= z; return *this;
}

// Scalar division
Vector3D Vector3D::operator/(const double f)
{
	return Vector3D(x / f, y / f, z / f);
}

Vector3D operator/(const double f, const Vector3D& v)
{
	return Vector3D(f / v.x, f / v.y, f / v.z);
}

Vector3D& Vector3D::operator/=(const double v)
{
	x /= v; y /= v; z /= v; return *this;
}

// Scalar addition
Vector3D Vector3D::operator+(const double f)
{
	return Vector3D(x + f, y + f, z + f);
}

Vector3D operator+(const double f, const Vector3D& v)
{
	return Vector3D(f + v.x, f + v.y, f + v.z);
}

Vector3D& Vector3D::operator+=(const double v)
{
	x += v; y += v; z += v; return *this;
}

// Scalar subtraction
Vector3D Vector3D::operator-(const double f)
{
	return Vector3D(x - f, y - f, z - f);
}

Vector3D operator-(const double f, const Vector3D& v)
{
	return Vector3D(f - v.x, f - v.y, f - v.z);
}

Vector3D& Vector3D::operator-=(const double v)
{
	x -= v; y -= v; z -= v; return *this;
}

// Conversion
Vector2D Vector3D::to2D() {
	return Vector2D(x, y);
}

Vector4D Vector3D::to4D() {
	return Vector4D(x, y, z, 1);
}



// ================================== VECTOR 4D =====================================

Vector4D::Vector4D(double _x, double _y, double _z, double _w) : x(_x), y(_y), z(_z), w(_w) { }

Vector4D::Vector4D(const Vector4D& v)
{
	x = v.x; y = v.y; z = v.z; w = v.w;
}

// Vector functions (Homogeneous coords, so the length only takes into account (x,y,z))
double Vector4D::length()
{
	return sqrt(quadrance());
}

double Vector4D::quadrance()
{
	return x * x + y * y + z * z;
}

Vector4D& Vector4D::normalize()
{
	double len = this->length();
	if (len == 0) throw "length = 0, can't normalize";
	double l = 1 / len;
	x *= l; y *= l; z *= l;
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
	return Vector4D(x + v.x, y + v.y, z + v.z, w);
}

Vector4D& Vector4D::operator+=(const Vector4D& v)
{
	x += v.x; y += v.y; z += v.z; return *this;
}

Vector4D Vector4D::operator-(const Vector4D& v)
{
	return Vector4D(x - v.x, y - v.y, z - v.z, w);
}

Vector4D& Vector4D::operator-=(const Vector4D& v)
{
	x -= v.x; y -= v.y; z -= v.z; return *this;
}

// Inner product (once again, 3D homogeneous)
double Vector4D::operator*(const  Vector4D& v)
{
	return x * v.x + y * v.y + z * v.z;
}

// Comparators - TODO: apply/support slight error (1E-5)
bool Vector4D::operator==(const Vector4D& v)
{
	if (this == &v) return true;
	return (abs(x - v.x) < EQERR && abs(y - v.y) < EQERR && abs(z - v.z) < EQERR && abs(w - v.w) < EQERR);
}

bool Vector4D::operator!=(const Vector4D& v)
{
	return !(*this == v);
}

bool Vector4D::equals(const Vector4D& v)
{
	if (this == &v) return true;
	return (x == v.x && y == v.y && z == v.z && w == v.w);
}

// Scalar multiplication
Vector4D Vector4D::operator*(double f)
{
	return Vector4D(x * f, y * f, z * f, w);
}

Vector4D operator*(const double f, const Vector4D& v)
{
	return Vector4D(f * v.x, f * v.y, f * v.z, v.w);
}

Vector4D& Vector4D::operator*=(const double v)
{
	x *= v; y *= v; z *= z; return *this;
}

// Scalar division
Vector4D Vector4D::operator/(double f)
{
	return Vector4D(x / f, y / f, z / f, w);
}

Vector4D operator/(const double f, const Vector4D& v)
{
	return Vector4D(f / v.x, f / v.y, f / v.z, v.w);
}

Vector4D& Vector4D::operator/=(const double v)
{
	x /= v; y /= v; z /= v; return *this;
}

// Scalar addition
Vector4D Vector4D::operator+(double f)
{
	return Vector4D(x + f, y + f, z + f, w);
}

Vector4D operator+(const double f, const Vector4D& v)
{
	return Vector4D(f + v.x, f + v.y, f + v.z, v.w);
}

Vector4D& Vector4D::operator+=(const double v)
{
	x += v; y += v; z += v; return *this;
}

// Scalar subtraction
Vector4D Vector4D::operator-(double f)
{
	return Vector4D(x - f, y - f, z - f, w);
}

Vector4D operator-(const double f, const Vector4D& v)
{
	return Vector4D(f - v.x, f - v.y, f - v.z, v.w);
}

Vector4D& Vector4D::operator-=(const double v)
{
	x -= v; y -= v; z -= v; return *this;
}

// Conversion
Vector2D Vector4D::to2D() {
	return Vector2D(x, y);
}

Vector3D Vector4D::to3D() {
	return Vector3D(x, y, z);
}

Vector4D& Vector4D::divideByW()
{
	*this /= w;
	w = 1.0f;
	return *this;
}
