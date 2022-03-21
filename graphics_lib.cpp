const Vector c_xOrigin = Vector(1, 0, 0);
const Vector c_yOrigin = Vector(0, 1, 0);
const Vector c_zOrigin = Vector(0, 0, 1);

unsigned int* pixel;

class zBuffer 
{
private:
	int width;
	int height;
	float* _zBuffer = nullptr;
public:
	zBuffer(int width, int height) 
	{
		this->width = width;
		this->height = height;
		_zBuffer = new float[width * height];
	}
	~zBuffer()
	{
		delete[] _zBuffer;
		_zBuffer = nullptr;
	}
	void Clear()
	{
		const int nDepth = width * height;
		for (int i = 0; i < nDepth; i++)
		{
			_zBuffer[i] = std::numeric_limits<float>::infinity();
		}
	}
	bool testAndUpdate(int x, int y, float z) 
	{
		if (_zBuffer[y * width + x] > z) 
		{
			_zBuffer[y * width + x] = z;
			return true;
		}
		return false;
	}
};

bool compare_float(float A, float B, float epsilon = 0.05f)
{
	return (abs(A - B) < epsilon);
}

void clear_screen() {
	pixel = (unsigned int*)g_bufferMemory;

	for (int y = 0; y < g_windowHeight; y++) {
		for (int x = 0; x < g_windowWidth; x++) {
			*pixel++ = 0X000000;
		}
	}
}

void fill_screen(short int r, short int g, short int b) {
	pixel = (unsigned int*)g_bufferMemory;

	for (int y = 0; y < g_windowHeight; y++) {
		for (int x = 0; x < g_windowWidth; x++) {
			*pixel++ = RGB(r,g,b);
		}
	}
}

void draw_flat_bottom_triangle(Point2D p0, Point2D p1, Point2D p2, Point color)
{
	float line_0_gradient = (p0.x - p2.x) / (p0.y - p2.y);
	float line_0_coefficient = p0.x - line_0_gradient * p0.y;

	float line_1_gradient = (p1.x - p2.x) / (p1.y - p2.y);
	float line_1_coefficient = p1.x - line_1_gradient * p1.y;

	int y_min = p0.y;

	int y_max = p2.y;

	if (y_min < 0)
	{
		y_min = 0;
	}
	if (y_max > g_windowHeight)
	{
		y_max = g_windowHeight;
	}

	for (int y = y_min; y < y_max; y++) {

		int x_border1 = round(line_0_gradient * y + line_0_coefficient);

		int x_border2 = round(line_1_gradient * y + line_1_coefficient);

		if (x_border1 < 0)
		{
			x_border1 = 0;
		}
		
		if (x_border2 > g_windowWidth)
		{
			x_border2 = g_windowWidth-1;
		}

		pixel = (unsigned int*)g_bufferMemory + x_border1 + y * g_windowWidth;

		for (int x = x_border1; x <= x_border2; x++)
		{
			*pixel++ = RGB(color.z, color.y, color.x);
		}

	}
}

void draw_flat_top_triangle(Point2D p0, Point2D p1, Point2D p2, Point color)
{
	float line_0_gradient = (p0.x - p1.x) / (p0.y - p1.y);
	float line_0_coefficient = p0.x - line_0_gradient * p0.y;

	float line_1_gradient = (p0.x - p2.x) / (p0.y - p2.y);
	float line_1_coefficient = p0.x - line_1_gradient * p0.y;

	int y_min = p0.y;

	int y_max = p2.y;

	if (y_min < 0)
	{
		y_min = 0;
	}
	if (y_max > g_windowHeight)
	{
		y_max = g_windowHeight;
	}

	for (int y = y_min; y < y_max; y++) {

		int x_border1 = round(line_0_gradient * y + line_0_coefficient);

		int x_border2 = round(line_1_gradient * y + line_1_coefficient);

		if (x_border1 < 0)
		{
			x_border1 = 0;
		}
		
		if (x_border2 > g_windowWidth)
		{
			x_border2 = g_windowWidth-1;
		}

		pixel = (unsigned int*)g_bufferMemory + x_border1 + y * g_windowWidth;

		for (int x = x_border1; x <= x_border2; x++)
		{
			*pixel++ = RGB(color.z, color.y, color.x);
		}
	}
}

void draw_triangle(Point2D* p0, Point2D* p1, Point2D* p2, Point* color)
{

	if (p0->y > p1->y) { std::swap(p0, p1); }
	if (p1->y > p2->y) { std::swap(p1, p2); }
	if (p0->y > p1->y) { std::swap(p1, p0); }

	if (compare_float(p0->y, p1->y))
	{
		if (p0->x > p1->x) { std::swap(p0, p1); }
		draw_flat_bottom_triangle(*p0, *p1, *p2, *color);
	}
	else if (compare_float(p1->y, p2->y))
	{
		if (p1->x > p2->x) { std::swap(p1, p2); }
		draw_flat_top_triangle(*p0, *p1, *p2, *color);
	}
	else
	{
		float AlphaSplit = (p1->y - p0->y) / (p2->y - p0->y);
		float x_split = p0->x + AlphaSplit * (p2->x - p0->x);

		Point2D ps = Point2D(x_split, p1->y);

		if (p1->x > x_split)
		{
			draw_flat_bottom_triangle(ps, *p1, *p2, *color);
			draw_flat_top_triangle(*p0, ps, *p1, *color);
		}
		else
		{
			draw_flat_bottom_triangle(*p1, ps, *p2, *color);
			draw_flat_top_triangle(*p0, *p1, ps, *color);
		}
	}
}

void draw_shape(Shape shape)
{
	std::chrono::milliseconds projectionTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
	std::vector<Point2D> BufferPoints2D;

	std::vector<Point>::iterator VerteciesIt = shape.vertecies.begin();

	for (; VerteciesIt < shape.vertecies.end(); VerteciesIt++) 
	{
		Vector VectorCamVert = Vector(player.position.x - VerteciesIt->x, player.position.y - VerteciesIt->y, player.position.z - VerteciesIt->z);

		float Zangle = player.zNormal.angleBetween(VectorCamVert);

		float Distance = VectorCamVert.lenght() * cos(Zangle);
		if (Distance > 0) {
			float PerspectiveDistortion = player.distabceToProjectionPlane / Distance;

			int ProjectionX = VectorCamVert.lenght() * cos(player.xNormal.angleBetween(VectorCamVert)) * PerspectiveDistortion * g_windowHeight / 21.6 + g_xDrawOffSet;
			int ProjectionY = VectorCamVert.lenght() * cos(player.yNormal.angleBetween(VectorCamVert)) * PerspectiveDistortion * g_windowHeight / 21.6 + g_yDrawOffSet;

			BufferPoints2D.push_back(Point2D(ProjectionX, ProjectionY));
		}
		else
		{
			BufferPoints2D.push_back(Point2D(-1, -1));
		}
		
	}
	projectionTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()) - projectionTime;
	std::chrono::milliseconds drawTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
	std::vector<Triangle>::iterator TrianglesIt = shape.tris.begin();
	int i = 60;
	for (; TrianglesIt < shape.tris.end(); TrianglesIt++)
	{
		Point2D* p0 = &BufferPoints2D[TrianglesIt->p0];
		Point2D* p1 = &BufferPoints2D[TrianglesIt->p1];
		Point2D* p2 = &BufferPoints2D[TrianglesIt->p2];

		float triangleFaceDirection = (p0->x * p1->y - p0->y * p1->x) + (p1->x * p2->y - p1->y * p2->x) + (p2->x * p0->y - p2->y * p0->x);

		if (p0->x != -1 and p1->x != -1 and p2->x != -1 and triangleFaceDirection>0) 
		{
			Point color = Point(i, i, i);
			drawCallCounter++;
			draw_triangle(p0, p1, p2, &color);
		}
		i += 10;
	}
	drawTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()) - drawTime;
	drawTimeSum += drawTime;
	projectionTimeSum += projectionTime;
}