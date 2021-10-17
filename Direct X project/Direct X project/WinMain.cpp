#include "Window.h"


int CALLBACK WinMain(
	HINSTANCE	hInstance,
	HINSTANCE	hPrevInstance,
	LPSTR		lpCmdLine,
	int			nCmdShow)
{
	Window WNDCLASS(400, 400, "Window Class revision (:");
	//message pump
	MSG msg;
	BOOL getResult;

	while ((getResult = GetMessage(&msg, nullptr, 0, 0)) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	if (getResult == -1)
	{
		return -1;
	}

	return msg.wParam;
}
