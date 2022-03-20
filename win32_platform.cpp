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

//Global Variables
bool bCLOSED = false;
bool showCursor = false;
int g_windowWidth = 1920;
int g_windowHeight = 1280;
int g_xDrawOffSet = g_windowWidth/2;
int g_yDrawOffSet = g_windowHeight/2;
void* g_bufferMemory;
std::string g_debug_folder_name = "";
BITMAPINFO g_bufferBitmapInfo;
std::vector<Shape> g_scene;
Camera player = Camera(Point(0, 0, 10));
Debugger Debug = Debugger();
POINT cursorPos;

std::chrono::milliseconds drawTimeSum;
std::chrono::milliseconds projectionTimeSum;
std::chrono::milliseconds deltaTime;
std::chrono::milliseconds frameStartTime;

#include "graphics_lib.cpp"
#include "callback_handler.cpp"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow) 
{
	create_debug_folder(&g_debug_folder_name);

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
	cube = create_cube();
	Shape plane;
	plane = create_plane();
	g_scene.push_back(cube);
	//g_scene.push_back(plane);

	float i = 0.01;

	while (!bCLOSED) 
	{

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

	//Clear Scene Memory
	std::vector<Shape>().swap(g_scene);
	_CrtDumpMemoryLeaks();

	Debug.Log("drawTimeSum : "+std::to_string(drawTimeSum.count()), &g_debug_folder_name);
	Debug.Log("projectionTimeSum : "+std::to_string(projectionTimeSum.count()), &g_debug_folder_name);

	return 0;
}