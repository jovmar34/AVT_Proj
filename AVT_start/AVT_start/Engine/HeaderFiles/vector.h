#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <cmath>
#include <cfloat>
using namespace std;

class Vector3D;
class Vector4D; 

class Vector2D
{
public:
	Vector2D() { };
	Vector2D(float x, float y);
	Vector2D(const Vector2D& v);

	float length();
	float quadrance();
	Vector2D& normalize();
	Vector2D operator=(const Vector2D& v);
	Vector2D operator+(const Vector2D& v);
	Vector2D operator-(const Vector2D& v);
	Vector2D operator*(float f);
	float  operator*(const Vector2D& v);   //inner product
	Vector2D operator/(float f);
	Vector2D& operator-=	(const Vector2D& v);
	Vector2D& operator+=	(const Vector2D& v);
	bool operator==	(const Vector2D& v);
	bool operator!=	(const Vector2D& v);
	Vector2D& operator-=	(const float v);
	Vector2D& operator*=	(const float v);
	Vector2D& operator/=	(const float v);
	Vector2D& operator+=	(const float v);
	Vector3D to3D();
	Vector4D to4D();

	float x;
	float y;

	friend inline
		istream& operator >>	(istream& s, Vector2D& v)
	{
		return s >> v.x >> v.y;
	}

	friend inline
		ostream& operator <<	(ostream& s, Vector2D& v)
	{
		s << "("<< v.x << "," << v.y << ")";
		return s;
	}

};

class Vector3D
{
public:
	Vector3D() { };
	Vector3D(float x, float y, float z);
	Vector3D(const Vector3D& v);

	float length();
	float quadrance();
	Vector3D& normalize();
	Vector3D operator=(const Vector3D& v);
	Vector3D operator+(const Vector3D& v);
	Vector3D operator-(const Vector3D& v);
	Vector3D operator*(float f);
	float  operator*(const Vector3D& v);   //inner product
	Vector3D operator/(float f);
	Vector3D operator%(const Vector3D& v); //external product
	Vector3D& operator-=	(const Vector3D& v);
	Vector3D& operator+=	(const Vector3D& v);
	bool operator==	(const Vector3D& v);
	bool operator!=	(const Vector3D& v);
	Vector3D& operator-=	(const float v);
	Vector3D& operator*=	(const float v);
	Vector3D& operator/=	(const float v);
	Vector3D& operator+=	(const float v);

	Vector2D to2D();
	Vector4D to4D();

	float x;
	float y;
	float z;

	friend inline
		istream& operator >>	(istream& s, Vector3D& v)
	{
		return s >> v.x >> v.y >> v.z;
	}

	friend inline
		ostream& operator <<	(ostream& s, Vector3D& v)
	{
		s << "(" << v.x << "," << v.y << "," << v.z << ")";
		return s;
	}

};

class Vector4D
{
public:
	Vector4D() { };
	Vector4D(float x, float y, float z, float w);
	Vector4D(const Vector4D& v);

	float length();
	float quadrance();
	Vector4D& normalize();
	Vector4D operator=(const Vector4D& v);
	Vector4D operator+(const Vector4D& v);
	Vector4D operator-(const Vector4D& v);
	Vector4D operator*(float f);
	float  operator*(const Vector4D& v);   //inner product
	Vector4D operator/(float f);
	Vector4D& operator-=	(const Vector4D& v);
	Vector4D& operator+=	(const Vector4D& v);
	bool operator==	(const Vector4D& v);
	bool operator!=	(const Vector4D& v);
	Vector4D& operator-=	(const float v);
	Vector4D& operator*=	(const float v);
	Vector4D& operator/=	(const float v);
	Vector4D& operator+=	(const float v);

	Vector2D to2D();
	Vector3D to3D();

	float x;
	float y;
	float z;
	float w;

	friend inline
		istream& operator >>	(istream& s, Vector4D& v)
	{
		return s >> v.x >> v.y >> v.z >> v.w;
	}

	friend inline
		ostream& operator <<	(ostream& s, Vector4D& v)
	{
		s << "(" << v.x << "," << v.y << "," << v.z << "," << v.w << ")";
		return s;
	}

};


#endif