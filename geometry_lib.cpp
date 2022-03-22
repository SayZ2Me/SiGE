#include "geometry_lib.h"

Point2D::Point2D(int x, int y, float d)
{
	this->x = x;
	this->y = y;
	this->d = d;
}

Point2D::Point2D()
{
	this->x = 0;
	this->y = 0;
	this->d = 0;
}

Point2D Point2D::operator+(Point2D& p)
{
	Point2D ret;
	ret.x = x + p.x;
	ret.y = y + p.y;
	ret.d = d + p.d;
	return ret;
}

Point2D Point2D::operator-(Point2D& p)
{
	Point2D ret;
	ret.x = x - p.x;
	ret.y = y - p.y;
	ret.d = d - p.d;
	return ret;
}

Triangle::Triangle(int p0, int p1, int p2)
{
	this->p0 = p0;
	this->p1 = p1;
	this->p2 = p2;
}

Point::Point(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Point::Point()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

Point Point::operator+(Point& p)
{
	Point ret;
	ret.x = x + p.x;
	ret.y = y + p.y;
	ret.z = z + p.z;
	return ret;
}

Point Point::operator-(Point& p)
{
	Point ret;
	ret.x = x - p.x;
	ret.y = y - p.y;
	ret.z = z - p.z;
	return ret;
}

Vector::Vector(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector::Vector(Point p0, Point p1)
{
	this->x = p0.x - p1.x;
	this->y = p0.y - p1.y;
	this->z = p0.z - p1.z;
}

Vector::Vector()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

float Vector::lenght()
{
	return (float)sqrt(x * x + y * y + z * z);
}

void Vector::normalize()
{
	this->x = this->x / this->lenght();
	this->y = this->y / this->lenght();
	this->z = this->z / this->lenght();
}

float Vector::angleBetween(Vector &v)
{
	float abs = this->lenght() * v.lenght();
	if (abs != 0) 
	{
		return acos(this->scalarProduct(v)/abs);
	}
	else 
	{
		return 0;
	}
}

float Vector::scalarProduct(Vector& v)
{
	return x * v.x + y * v.y + z * v.z;
}

void Vector::rotate_x(float y, float z, float angle)
{
	this->y = y * cos(angle) + z * sin(angle);
	this->z = y * -sin(angle) + z * cos(angle);
}
void Vector::rotate_y(float x, float z, float angle)
{
	this->x = x * cos(angle) + z * -sin(angle);
	this->z = x * sin(angle) + z * cos(angle);
}
void Vector::rotate_z(float x, float y, float angle)
{
	this->x = x * cos(angle) + y * sin(angle);
	this->y = x * -sin(angle) + y * cos(angle);
}

Vector Vector::operator+(Vector& v)
{
	Vector ret;
	ret.x = x + v.x;
	ret.y = y + v.y;
	ret.z = z + v.z;
	return ret;
}

Vector Vector::operator-(Vector& v)
{
	Vector ret;
	ret.x = x - v.x;
	ret.y = y - v.y;
	ret.z = z - v.z;
	return ret;
}

Vector Vector::operator*(Vector& v)
{
	Vector ret;
	ret.x = y * v.z - z * v.y;
	ret.y = x * v.z - z * v.x;
	ret.z = x * v.y - y * v.x;
	return ret;
}