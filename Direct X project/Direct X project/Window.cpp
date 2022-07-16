
#include "Window.h"
#include <iostream>
#include <sstream>


Window::WindowClass Window::WindowClass::wndClass;

Window::WindowClass::WindowClass() noexcept :
	hInst(GetModuleHandle(nullptr))
{
	// register windows class
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = HandleMsgSetup;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = GetInstance();
	wc.hIcon = nullptr;
	wc.hCursor = nullptr;
	wc.hbrBackground = nullptr;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = GetName();
	wc.hIconSm = nullptr;
	RegisterClassEx(&wc);
}

Window::WindowClass::~WindowClass()
{
	UnregisterClass(wndClassName, GetInstance());
}

const char* Window::WindowClass::GetName() noexcept
{
	return wndClassName;
}
HINSTANCE Window::WindowClass::GetInstance() noexcept
{
	return wndClass.hInst;
}

Window::Window(int width, int height, const char* name)
	:
	width(width),
	height(height)
{
	//values for calculating windows size based on the client area of the window
	RECT wr;
	wr.left = 100;
	wr.right = width + wr.left;
	wr.top = 100;
	wr.bottom = height + wr.top;

	AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE);
	hWnd = CreateWindow(
		WindowClass::GetName(), name,
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT, wr.right - wr.left, wr.bottom - wr.top,
		nullptr, nullptr, WindowClass::GetInstance(), this);

	ShowWindow(hWnd, SW_SHOWDEFAULT);

	pRenderer = std::make_unique<Renderer> (hWnd);
}

Window::~Window()
{
	DestroyWindow(hWnd);
}

LRESULT CALLBACK Window::HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	if (msg == WM_NCCREATE)
	{
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
		Window* const pWnd = static_cast<Window*>(pCreate->lpCreateParams);
		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::HandleMsgThunk));
		return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT CALLBACK Window::HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	Window* const pWnd = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
}

LRESULT Window::HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	switch (msg)
	{
		//on close window
		case WM_CLOSE:
		{
			PostQuitMessage(000);
			return 0;
		}
		case WM_KILLFOCUS:
		{
			keyboard.clearState();
			break;
		}

		//keyboard input
		case WM_KEYDOWN:
		{
			if (!(lParam & 0x40000000) || keyboard.isAutoRepeatEnabled())
			{
				keyboard.onKeyPressed(static_cast<unsigned char>(wParam));
			}
			break;
		}
		case WM_KEYUP:
		{
			keyboard.onKeyReleased(static_cast<unsigned char>(wParam));
			break;
		}		
		case WM_CHAR:
		{
			keyboard.onChar(static_cast<unsigned char>(wParam));
			break;
		}


		//mouse input
		case WM_LBUTTONDOWN:
		{
			//changes windows title to mouse coords
			const POINTS pt = MAKEPOINTS(lParam);
			std::ostringstream oss;
			oss << "(" << pt.x << "," << pt.y << ")";
			SetWindowTitle(oss.str());
			break;
		}
		case WM_MOUSEMOVE:
		{
			POINT mp;
			GetCursorPos(&mp);

			mouseX = mp.x;
			mouseY = mp.y;
			//OutputDebugString("ding");
			break;
		}
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

void Window::SetWindowTitle(const std::string& title)
{
	if (SetWindowText (hWnd, title.c_str()) == 0)
	{
		//throw WND_PREVIOUS_EXCEPT();
	}
}


std::optional<int> Window::ProcessMessages()
{
	MSG msg;
	//BOOL getResult;

	while ((PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) > 0)
	{
		if (msg.message == WM_QUIT)
		{
			return msg.wParam;
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return{};
	/*if (getResult == -1)
	{
		return -1;
	}

	return msg.wParam;*/
}

Renderer& Window::Render()
{
	return *pRenderer;
}

Window::Exception::Exception(int line, const char* file, HRESULT hr) noexcept
	:
	ExceptionHandler(line, file),
	hr(hr)
{}

const char* Window::Exception::GetType() const noexcept
{
	return "Window Exception";
}


const char* Window::Exception::what() const noexcept
{
	std::ostringstream oss;
	oss << GetType() << std::endl
		<< "[ERROR CODE] " << GetErrorCode() << std::endl
		<< "[DESCRIPTION] " << GetErrorString() << std::endl
		<< GetOriginString();
	whatBuffer = oss.str();
	return whatBuffer.c_str();
}

std::string Window::Exception::TranslateErrorCode(HRESULT hr) noexcept
{
	char* pMsgBuf = nullptr;
	DWORD nMsgLen = FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS, nullptr, hr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		reinterpret_cast<LPSTR>(&pMsgBuf), 0, nullptr);
	if (nMsgLen == 0)
	{
		return "Unidentified error code";
	}
	std::string errorString = pMsgBuf;
	LocalFree(pMsgBuf);
	return errorString;
}

HRESULT Window::Exception::GetErrorCode() const noexcept
{
	return hr;
}
std::string Window::Exception::GetErrorString() const noexcept
{
	return TranslateErrorCode(hr);
}
