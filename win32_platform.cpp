#include <windows.h>
#include <winuser.h>
#undef min
#undef max
#include <string>
#include <ctime>
#include <iostream>
#include "app_info.h"
#include "objects_lib.h"
#include "dev_tools.h"
#include <chrono>

#define __CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW

bool bCLOSED = false;
bool showCursor = false;
int g_windowWidth = 1920;
int g_windowHeight = 1280;
int g_xDrawOffSet = g_windowWidth/2;
int g_yDrawOffSet = g_windowHeight/2;
void* g_bufferMemory;
float* g_zBuffer;
BITMAPINFO g_bufferBitmapInfo;
std::vector<Shape> g_scene;
Camera player = Camera(Point(0, 0, 10));
Debugger Debug = Debugger();
POINT cursorPos;
LightSource g_Illumination = LightSource(Point(0, 0, 0), Vector(-0.25, -0.5, -1));

std::chrono::milliseconds drawTimeSum;
std::chrono::milliseconds projectionTimeSum;
std::chrono::milliseconds deltaTime;
std::chrono::milliseconds frameStartTime;
std::chrono::milliseconds programmStartTime;
std::chrono::milliseconds programmEndTime;
int drawCallCounter = 0;
int frameCounter = 0;

#include "graphics_lib.cpp"
#include "callback_handler.cpp"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow) 
{
	create_debug_folder(&Debug);

	Debug.log("Debug start");

	const wchar_t className[] = L"Standart Window Class";

	WNDCLASS windowClass = {};
	windowClass.style = CS_HREDRAW | CS_VREDRAW;
	windowClass.lpszClassName = className;
	windowClass.lpfnWndProc = WindowProc;

	RegisterClass(&windowClass);

	HWND window = CreateWindow(windowClass.lpszClassName, appVersion, WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 1920, 1280, 0, 0, hInstance, 0);
	HDC hdc = GetDC(window);

	ShowCursor(showCursor);
	
	Shape cube;
	for (int x = 0; x < 10; x++)
	{
		for (int y = 0; y < 10; y++)
		{
			for (int z = 0; z < 10; z++)
			{
				cube = create_cube();
				cube.set_color(100+x, 50+y*20, 20+z*30);
				move_x_axis(&cube, x);
				move_y_axis(&cube, y);
				move_z_axis(&cube, z);
				g_scene.push_back(cube);
			}
		}
	}

	programmStartTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());

	while (!bCLOSED) 
	{
		frameCounter++;
		frameStartTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
		MSG message;
		while (PeekMessage(&message, window, 0, 0, PM_REMOVE)) 
		{
			TranslateMessage(&message);
			DispatchMessage(&message);
		}

		GetCursorPos(&cursorPos);

		clear_screen();

		for (int i =0;i< g_scene.size();i++)
		{
			draw_shape(g_scene[i]);
		}

		player.move(deltaTime.count());

		player.rotate((float)cursorPos.x, -(float)cursorPos.y);

		StretchDIBits(hdc, 0, 0, g_windowWidth, g_windowHeight, 0, 0, g_windowWidth, g_windowHeight, g_bufferMemory, &g_bufferBitmapInfo, DIB_RGB_COLORS, SRCCOPY);

		deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()) - frameStartTime;
	}
	programmEndTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()); 
	
	if (g_bufferMemory) {
		Debug.log("Mem realeased");
		VirtualFree(g_bufferMemory, 0, MEM_RELEASE);
	}
	delete[] g_zBuffer;
	std::vector<Shape>().swap(g_scene);
	_CrtDumpMemoryLeaks();

	Debug.log("drawTimeSum : " + std::to_string(drawTimeSum.count()));
	Debug.log("projectionTimeSum : " + std::to_string(projectionTimeSum.count()));
	Debug.log("drawCallCounter : " + std::to_string(drawCallCounter));
	Debug.log("avgFPS : " + std::to_string(frameCounter / ((programmEndTime.count() - programmStartTime.count()) / 1000)));
	Debug.log("Debug end");

	return 0;
}