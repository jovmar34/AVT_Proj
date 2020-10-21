#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <cmath>
#include <cfloat>
#include <GL\glew.h>

using namespace std;

#define EQERR 1E-5

class Vector2D;
class Vector3D;
class Vector4D; 

class Vector2D
{
public:
	// Attributes
	double x;
	double y;
	GLfloat data[2] = { 0,0 };

	Vector2D() : x(0), y(0) { };
	Vector2D(double x, double y);
	Vector2D(const Vector2D& v);

	// Vector functions
	double		length();
	double		quadrance();
	Vector2D&	normalize();

	// Vector assignment, addition and subtraction
	Vector2D operator=		(const Vector2D& v);
	
	Vector2D operator+		(const Vector2D& v);
	Vector2D& operator+=	(const Vector2D& v);

	Vector2D operator-		(const Vector2D& v);
	Vector2D& operator-=	(const Vector2D& v);

	// Inner product
	double operator* (const Vector2D& v);

	// Comparators
	bool operator==	(const Vector2D& v);
	bool operator!=	(const Vector2D& v);
	bool equals		(const Vector2D& v);

	// Scalar multiplication
	Vector2D operator*			(const double f);
	friend Vector2D operator*	(const double f, const Vector2D& v);
	Vector2D& operator*=		(const double v);

	// Scalar division
	Vector2D operator/			(const double f);
	friend Vector2D operator/	(const double f, const Vector2D& v);
	Vector2D& operator/=		(const double v);
	
	// Scalar addition
	Vector2D operator+			(double f);
	friend Vector2D operator+	(double f, const Vector2D& v);
	Vector2D& operator+=		(const double v);
	
	// Scalar subtraction
	Vector2D operator-			(double f);
	friend Vector2D operator-	(double f, const Vector2D& v);
	Vector2D& operator-=		(const double v);
	
	// Conversion
	Vector3D to3D();
	Vector4D to4D();

	// Open GL
	GLfloat* toOpenGL() {
		data[0] = (GLfloat) x;
		data[1] = (GLfloat) y;
		return data;
	}

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
	// Attributes
	double x;
	double y;
	double z;

	GLfloat data[3] = {0,0,0};

	Vector3D(): x(0), y(0), z(0) { };
	Vector3D(double x, double y, double z);
	Vector3D(const Vector3D& v);

	// Vector functions
	double length();
	double quadrance();
	Vector3D& normalize();

	// Vector assignment, addition and subtraction
	Vector3D operator=		(const Vector3D& v);

	Vector3D operator+		(const Vector3D& v);
	Vector3D& operator+=	(const Vector3D& v);

	Vector3D operator-		(const Vector3D& v);
	Vector3D& operator-=	(const Vector3D& v);

	// Inner and Cross product
	double  operator*	(const Vector3D& v);   
	Vector3D operator%	(const Vector3D& v); 

	// Comparators
	bool operator==	(const Vector3D& v);
	bool operator!=	(const Vector3D& v);
	bool equals		(const Vector3D& v);

	// Scalar multiplication
	Vector3D operator*			(const double f);
	friend Vector3D operator*	(const double f, const Vector3D& v);
	Vector3D& operator*=		(const double f);

	// Scalar division
	Vector3D operator/			(const double f);
	friend Vector3D operator/	(const double f, const Vector3D& v);
	Vector3D& operator/=		(const double f);

	// Scalar addition
	Vector3D operator+			(const double f);
	friend Vector3D operator+	(const double f, const Vector3D& v);
	Vector3D& operator+=		(const double f);

	// Scalar subtraction
	Vector3D operator-			(const double f);
	friend Vector3D operator-	(const double f, const Vector3D& v);
	Vector3D& operator-=		(const double fv);

	// Conversion
	Vector2D to2D();
	Vector4D to4D();

	// Open GL
	GLfloat* toOpenGL() {
		data[0] = (GLfloat) x;
		data[1] = (GLfloat) y;
		data[2] = (GLfloat) z;
		return data;
	}

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
	// Attributes
	double x;
	double y;
	double z;
	double w;

	GLfloat data[4] = { 0,0,0,0 };

	Vector4D(): x(0), y(0), z(0), w(1) { };
	Vector4D(double x, double y, double z, double w);
	Vector4D(const Vector4D& v);

	// Vector functions
	double		length();
	double		quadrance();
	Vector4D&	normalize();

	// Vector assignment, addition and subtraction
	Vector4D operator=		(const Vector4D& v);

	Vector4D operator+		(const Vector4D& v);
	Vector4D& operator+=	(const Vector4D& v);

	Vector4D operator-		(const Vector4D& v);
	Vector4D& operator-=	(const Vector4D& v);

	// Inner product
	double  operator*(const Vector4D& v);

	// Comparators
	bool operator==	(const Vector4D& v);
	bool operator!=	(const Vector4D& v);
	bool equals		(const Vector4D& v);

	// Scalar multiplication
	Vector4D operator*			(double f);
	friend Vector4D operator*	(const double f, const Vector4D& v);
	Vector4D& operator*=		(const double v);

	// Scalar division
	Vector4D operator/			(double f);
	friend Vector4D operator/	(const double f, const Vector4D& v);
	Vector4D& operator/=		(const double v);

	// Scalar addition
	Vector4D operator+			(double f);
	friend Vector4D operator+	(const double f, const Vector4D& v);
	Vector4D& operator+=		(const double v);

	// Scalar subtraction
	Vector4D operator-			(double f);
	friend Vector4D operator-	(const double f, const Vector4D& v);
	Vector4D& operator-=		(const double v);

	// Conversion
	Vector2D to2D();
	Vector3D to3D();

	// Open GL
	GLfloat* toOpenGL() {
		data[0] = (GLfloat)x;
		data[1] = (GLfloat)y;
		data[2] = (GLfloat)z;
		data[3] = (GLfloat)w;
		return data;
	}


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