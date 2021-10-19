
#include "App.h"


int CALLBACK WinMain(
	HINSTANCE	hInstance,
	HINSTANCE	hPrevInstance,
	LPSTR		lpCmdLine,
	int			nCmdShow)
{
	//Window WNDCLASS(400, 400, "Window Class revision (:");
	//message pump
	try
	{
		return App{}.init();
	}

	catch (const ExceptionHandler& e)
	{
		MessageBox(nullptr, e.what(), e.GetType(), MB_OK | MB_ICONERROR);
	}
	catch (const std::exception& e)
	{
		MessageBox(nullptr, e.what(), "Standard Exception", MB_OK | MB_ICONERROR);
	}
	catch (...)
	{
		MessageBox(nullptr, "No Details Available", "Unknown Exception", MB_OK | MB_ICONERROR);
	}

	return -1;

}
