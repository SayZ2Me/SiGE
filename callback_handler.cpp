LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;
	switch (uMsg)
	{
	case WM_CLOSE:
	case WM_DESTROY: {
		projectionTimeSum;
		drawTimeSum;
		int a = 0;
		bCLOSED = true;
	}break;

	case WM_KEYDOWN:
	{
		if (LOWORD(wParam) == 68)
		{
			player.set_x_movement(-1);
			break;
		}
		if (LOWORD(wParam) == 65)
		{
			player.set_x_movement(1);
			break;
		}
		if (LOWORD(wParam) == 87)
		{
			player.set_z_movement(-1);
			break;
		}
		if (LOWORD(wParam) == 83)
		{
			player.set_z_movement(1);
			break;
		}
		switch (LOWORD(wParam))
		{
		case VK_RIGHT:
		{
			player.set_x_movement(-1);
			break;
		}
		case VK_LEFT:
		{
			player.set_x_movement(1);
			break;
		}
		case VK_UP:
		{
			player.set_z_movement(-1);
			break;
		}
		case VK_DOWN:
		{
			player.set_z_movement(1);
			break;
		}
		case VK_SPACE:
		{
			player.set_y_movement(-1);
			break;
		}
		case VK_SHIFT:
		{
			player.set_y_movement(1);
			break;
		}
		case VK_ESCAPE:
		{
			showCursor = !showCursor;
			ShowCursor(showCursor);
			break;
		}
		default:
			break;
		}
	}break;

	case WM_KEYUP:
	{
		if (LOWORD(wParam) == 68 or LOWORD(wParam) == 65)
		{
			player.set_x_movement(0);
			break;
		}
		if (LOWORD(wParam) == 87 or LOWORD(wParam) == 83)
		{
			player.set_z_movement(0);
			break;
		}
		switch (LOWORD(wParam))
		{
		case VK_RIGHT:
		{
			player.set_x_movement(0);
			break;
		}
		case VK_LEFT:
		{
			player.set_x_movement(0);
			break;
		}
		case VK_UP:
		{
			player.set_z_movement(0);
			break;
		}
		case VK_DOWN:
		{
			player.set_z_movement(0);
			break;
		}
		case VK_SPACE:
		{
			player.set_y_movement(0);
			break;
		}
		case VK_SHIFT:
		{
			player.set_y_movement(0);
			break;
		}
		default:
			break;
		}
	}break;

	case WM_SIZE: {
		RECT rect;
		GetClientRect(hwnd, &rect);
		g_windowWidth = rect.right - rect.left;
		g_windowHeight = rect.bottom - rect.top;
		g_xDrawOffSet = g_windowWidth / 2;
		g_yDrawOffSet = g_windowHeight / 2;

		int bufferSize = g_windowWidth * g_windowHeight * sizeof(unsigned int);
		if (g_bufferMemory) {
			VirtualFree(g_bufferMemory, 0, MEM_RELEASE);
		}
		g_bufferMemory = VirtualAlloc(0, bufferSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

		g_bufferBitmapInfo.bmiHeader.biSize = sizeof(g_bufferBitmapInfo.bmiHeader);
		g_bufferBitmapInfo.bmiHeader.biWidth = g_windowWidth;
		g_bufferBitmapInfo.bmiHeader.biHeight = g_windowHeight;
		g_bufferBitmapInfo.bmiHeader.biPlanes = 1;
		g_bufferBitmapInfo.bmiHeader.biBitCount = 32;
		g_bufferBitmapInfo.bmiHeader.biCompression = BI_RGB;

	}break;

	default: {
		result = DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	}
	return result;
}