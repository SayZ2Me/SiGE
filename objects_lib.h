#include "geometry_lib.h"
#include <vector>
#include <utility>
#include <algorithm>
#include <initializer_list>

#pragma once

class Camera 
{
private:
	float x_movement;
	float y_movement;
	float z_movement;
public:
	Point position;

	Vector xNormal;
	Vector yNormal;
	Vector zNormal;

	float distabceToProjectionPlane;

	Camera(Point pos);

	void move(unsigned int deltaTime);

	void set_x_movement(float x);
	void set_y_movement(float y);
	void set_z_movement(float z);

	void rotate(float x, float y);
};

class Shape
{
public:
	std::vector<Point> vertecies;
	std::vector<Triangle> tris;
	Point color;

	Shape();
	~Shape();

	void add_point(Point);
	void add_tris(int p0, int p1, int p2);
	void set_color(int r, int g, int b);
};

Shape create_cube();
Shape create_plane();

void rotate_x_axis(Shape* shape, float angle);
void rotate_y_axis(Shape* shape, float angle);
void rotate_z_axis(Shape* shape, float angle);
void scale_x_axis(Shape* shape, float scale);
void scale_y_axis(Shape* shape, float scale);
void scale_z_axis(Shape* shape, float scale);
void move_x_axis(Shape* shape, float x);
void move_y_axis(Shape* shape, float y);
void move_z_axis(Shape* shape, float z);