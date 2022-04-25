#include "objects_lib.h"

Camera::Camera(Point pos) 
{
	this->position = pos;

	xNormal = Vector(1, 0, 0);
	yNormal = Vector(0, 1, 0);
	zNormal = Vector(0, 0, 1);

	distabceToProjectionPlane = 10;
}

void Camera::move(unsigned int deltaTime)
{
	position.x += x_movement * xNormal.x * deltaTime / 100 + y_movement * yNormal.x * deltaTime / 100 + z_movement * zNormal.x * deltaTime / 100;
	position.y += x_movement * xNormal.y * deltaTime / 100 + y_movement * yNormal.y * deltaTime / 100 + z_movement * zNormal.y * deltaTime / 100;
	position.z += x_movement * xNormal.z * deltaTime / 100 + y_movement * yNormal.z * deltaTime / 100 + z_movement * zNormal.z * deltaTime / 100;
}

void Camera::set_x_movement(float x) 
{
	x_movement = x;
}
void Camera::set_y_movement(float y)
{
	y_movement = y;
}
void Camera::set_z_movement(float z)
{
	z_movement = z;
}

void Camera::rotate(float x, float y)
{
	x = x * M_PI / 180;
	y = y * M_PI / 180;
	Vector defxNormal = Vector(1, 0, 0);
	Vector defyNormal = Vector(0, 1, 0);
	Vector defzNormal = Vector(0, 0, 1);
	defxNormal.rotate_x(defxNormal.y, defxNormal.z, y);
	defyNormal.rotate_x(defyNormal.y, defyNormal.z, y);
	defzNormal.rotate_x(defzNormal.y, defzNormal.z, y);
	defxNormal.rotate_y(defxNormal.x, defxNormal.z, x);
	defyNormal.rotate_y(defyNormal.x, defyNormal.z, x);
	defzNormal.rotate_y(defzNormal.x, defzNormal.z, x);
	xNormal = defxNormal;
	yNormal = defyNormal;
	zNormal = defzNormal;
}

LightSource::LightSource(Point position, Vector direction) 
{
	this->position = position;
	this->direction = direction;
}
LightSource::~LightSource() {}
Point LightSource::get_position()
{
	return this->position;
}
Vector LightSource::get_direction()
{
	return this->direction;
}

Shape::Shape() {}
Shape::~Shape() 
{
	vertecies.clear();
	tris.clear();
}

void Shape::add_point(Point p)
{
	vertecies.push_back(p);
}

void Shape::add_tris(int p0, int p1, int p2)
{
	tris.push_back(Triangle(p0, p1, p2));
}

void Shape::set_color(int r, int g, int b)
{
	this->color = Point(r, g, b);
}

Shape create_cube()
{
	Shape cube = Shape();
	for (int x = 0; x < 2; x++) {
		for (int y = 0; y < 2; y++) {
			for (int z = 0; z < 2; z++) {
				cube.add_point(Point(((float)x * 2 - 1)/5, ((float)y * 2 - 1)/5, ((float)z * 2 - 1)/5));
			}
		}
	}

	cube.add_tris(1, 3, 0);
	cube.add_tris(0, 3, 2);

	cube.add_tris(5, 6, 7);
	cube.add_tris(5, 4, 6);

	cube.add_tris(1, 0, 4);
	cube.add_tris(1, 4, 5);

	cube.add_tris(3, 6, 2);
	cube.add_tris(3, 7, 6);

	cube.add_tris(0, 2, 4);
	cube.add_tris(4, 2, 6);

	cube.add_tris(5, 7, 1);
	cube.add_tris(1, 7, 3);

	return cube;
}

Shape create_plane()
{
	Shape plane = Shape();

	plane.add_point(Point(-1, -1, 0));
	plane.add_point(Point(1, -1, 0));
	plane.add_point(Point(-1, 1, 0));
	plane.add_point(Point(1, 1, 0));

	plane.add_tris(0, 1, 2);
	plane.add_tris(1, 3, 2);

	return plane;
}

Shape create_triangle()
{
	Shape triangle = Shape();

	triangle.add_point(Point(-1, -1, 0));
	triangle.add_point(Point(1, -1, 0));
	triangle.add_point(Point(0, 1, 0));

	triangle.add_tris(0, 1, 2);

	return triangle;
}

void rotate_x_axis(Shape* shape, float angle)
{
	std::vector<Point>::iterator it = shape->vertecies.begin();
	for (; it < shape->vertecies.end(); it++)
	{
		float y1 = it->y * cos(angle) - it->z * sin(angle);
		float z1 = it->z * cos(angle) + it->y * sin(angle);
		it->y = y1;
		it->z = z1;
	}
}

void rotate_y_axis(Shape* shape, float angle)
{
	std::vector<Point>::iterator it = shape->vertecies.begin();
	for (; it < shape->vertecies.end(); it++)
	{
		float x1 = it->x * cos(angle) - it->z * sin(angle);
		float z1 = it->z * cos(angle) + it->x * sin(angle);
		it->x = x1;
		it->z = z1;
	}
}

void rotate_z_axis(Shape* shape, float angle)
{
	std::vector<Point>::iterator it = shape->vertecies.begin();
	for (; it < shape->vertecies.end(); it++)
	{
		float x1 = it->x * cos(angle) - it->y * sin(angle);
		float y1 = it->y * cos(angle) + it->x * sin(angle);
		it->x = x1;
		it->y = y1;
	}
}

void scale_x_axis(Shape* shape, float scale)
{
	std::vector<Point>::iterator it = shape->vertecies.begin();
	for (; it < shape->vertecies.end(); it++)
	{
		it->x *= scale;
	}
}

void scale_y_axis(Shape* shape, float scale)
{
	std::vector<Point>::iterator it = shape->vertecies.begin();
	for (; it < shape->vertecies.end(); it++)
	{
		it->y *= scale;
	}
}

void scale_z_axis(Shape* shape, float scale)
{
	std::vector<Point>::iterator it = shape->vertecies.begin();
	for (; it < shape->vertecies.end(); it++)
	{
		it->z *= scale;
	}
}

void move_x_axis(Shape* shape, float x)
{
	std::vector<Point>::iterator it = shape->vertecies.begin();
	for (; it < shape->vertecies.end(); it++)
	{
		it->x += x;
	}
}

void move_y_axis(Shape* shape, float y)
{
	std::vector<Point>::iterator it = shape->vertecies.begin();
	for (; it < shape->vertecies.end(); it++)
	{
		it->y += y;
	}
}

void move_z_axis(Shape* shape, float z)
{
	std::vector<Point>::iterator it = shape->vertecies.begin();
	for (; it < shape->vertecies.end(); it++)
	{
		it->z += z;
	}
}