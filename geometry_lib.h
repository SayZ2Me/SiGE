#define _USE_MATH_DEFINES
#include <math.h>

#pragma once

class Point2D
{
public:
	float x = 0;
	float y = 0;

	Point2D(int x, int y);
	Point2D();

	Point2D operator+ (Point2D& p);
	Point2D operator- (Point2D& p);
};

class Triangle 
{
public:
	int p0;
	int p1;
	int p2;

	Triangle(int p0, int p1, int p2);
};

class Point
{
public:
	float x = 0;
	float y = 0;
	float z = 0;

	Point(float x, float y, float z);
	Point();

	Point operator+ (Point& p);
	Point operator- (Point& p);
};

class Vector
{
public:
	float x = 0;
	float y = 0;
	float z = 0;

	Vector(float x, float y, float z);
	Vector();

	float lenght();
	void normalize();
	float scalarProduct(Vector& v);
	float angleBetween(Vector& v);
	void rotate_x(float y, float z, float angle);
	void rotate_y(float x, float z, float angle);
	void rotate_z(float x, float y, float angle);

	Vector operator+ (Vector& p);
	Vector operator- (Vector& p);
	Vector operator* (Vector& p);
};