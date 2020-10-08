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

	// Attributes
	float x;
	float y;

	// Vector functions
	float		length();
	float		quadrance();
	Vector2D&	normalize();

	// Vector assignment, addition and subtraction
	Vector2D operator=		(const Vector2D& v);
	
	Vector2D operator+		(const Vector2D& v);
	Vector2D& operator+=	(const Vector2D& v);

	Vector2D operator-		(const Vector2D& v);
	Vector2D& operator-=	(const Vector2D& v);

	// Inner product
	float operator* (const Vector2D& v);

	// Comparators
	bool operator==	(const Vector2D& v);
	bool operator!=	(const Vector2D& v);

	// Scalar multiplication
	Vector2D operator*			(const float f);
	friend Vector2D operator*	(const float f, const Vector2D& v);
	Vector2D& operator*=		(const float v);

	// Scalar division
	Vector2D operator/			(const float f);
	friend Vector2D operator/	(const float f, const Vector2D& v);
	Vector2D& operator/=		(const float v);
	
	// Scalar addition
	Vector2D operator+			(float f);
	friend Vector2D operator+	(float f, const Vector2D& v);
	Vector2D& operator+=		(const float v);
	
	// Scalar subtraction
	Vector2D operator-			(float f);
	friend Vector2D operator-	(float f, const Vector2D& v);
	Vector2D& operator-=		(const float v);
	
	// Conversion
	Vector3D to3D();
	Vector4D to4D();

	// Stream operators
	friend inline istream& operator >> (istream& s, Vector2D& v)
	{
		return s >> v.x >> v.y;
	}

	friend inline ostream& operator << (ostream& s, Vector2D& v)
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

	// Attributes
	float x;
	float y;
	float z;

	// Vector functions
	float length();
	float quadrance();
	Vector3D& normalize();

	// Vector assignment, addition and subtraction
	Vector3D operator=		(const Vector3D& v);

	Vector3D operator+		(const Vector3D& v);
	Vector3D& operator+=	(const Vector3D& v);

	Vector3D operator-		(const Vector3D& v);
	Vector3D& operator-=	(const Vector3D& v);

	// Inner and Cross product
	float  operator*	(const Vector3D& v);   
	Vector3D operator%	(const Vector3D& v); 

	// Comparators
	bool operator==	(const Vector3D& v);
	bool operator!=	(const Vector3D& v);

	// Scalar multiplication
	Vector3D operator*			(const float f);
	friend Vector3D operator*	(const float f, const Vector3D& v);
	Vector3D& operator*=		(const float f);

	// Scalar division
	Vector3D operator/			(const float f);
	friend Vector3D operator/	(const float f, const Vector3D& v);
	Vector3D& operator/=		(const float f);

	// Scalar addition
	Vector3D operator+			(const float f);
	friend Vector3D operator+	(const float f, const Vector3D& v);
	Vector3D& operator+=		(const float f);

	// Scalar subtraction
	Vector3D operator-			(const float f);
	friend Vector3D operator-	(const float f, const Vector3D& v);
	Vector3D& operator-=		(const float fv);

	// Conversion
	Vector2D to2D();
	Vector4D to4D();

	// Stream operators
	friend inline istream& operator >> (istream& s, Vector3D& v)
	{
		return s >> v.x >> v.y >> v.z;
	}

	friend inline ostream& operator << (ostream& s, Vector3D& v)
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

	// Attributes
	float x;
	float y;
	float z;
	float w;

	// Vector functions
	float		length();
	float		quadrance();
	Vector4D&	normalize();

	// Vector assignment, addition and subtraction
	Vector4D operator=		(const Vector4D& v);

	Vector4D operator+		(const Vector4D& v);
	Vector4D& operator+=	(const Vector4D& v);

	Vector4D operator-		(const Vector4D& v);
	Vector4D& operator-=	(const Vector4D& v);

	// Inner product
	float  operator*(const Vector4D& v);

	// Comparators
	bool operator==	(const Vector4D& v);
	bool operator!=	(const Vector4D& v);

	// Scalar multiplication
	Vector4D operator*			(float f);
	friend Vector4D operator*	(const float f, const Vector4D& v);
	Vector4D& operator*=		(const float v);

	// Scalar division
	Vector4D operator/			(float f);
	friend Vector4D operator/	(const float f, const Vector4D& v);
	Vector4D& operator/=		(const float v);

	// Scalar addition
	Vector4D operator+			(float f);
	friend Vector4D operator+	(const float f, const Vector4D& v);
	Vector4D& operator+=		(const float v);

	// Scalar subtraction
	Vector4D operator-			(float f);
	friend Vector4D operator-	(const float f, const Vector4D& v);
	Vector4D& operator-=		(const float v);

	// Conversion
	Vector2D to2D();
	Vector3D to3D();

	// Stream operators
	friend inline istream& operator >> (istream& s, Vector4D& v)
	{
		return s >> v.x >> v.y >> v.z >> v.w;
	}

	friend inline ostream& operator << (ostream& s, Vector4D& v)
	{
		s << "(" << v.x << "," << v.y << "," << v.z << "," << v.w << ")";
		return s;
	}
};

#endif