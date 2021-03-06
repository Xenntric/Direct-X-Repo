
#pragma once
#include <Windows.h>
#include <optional>
#include <memory>
#include "ExceptionHandler.h"
#include "Renderer.h"
#include "KeyboardClass.h"

class Window
{
public:
	class Exception : public ExceptionHandler
	{
	public:
		Exception(int line, const char* file, HRESULT hr) noexcept;
		const char* what() const noexcept override;
		virtual const char* GetType() const noexcept override;
		static std::string TranslateErrorCode(HRESULT hr) noexcept;
		HRESULT GetErrorCode() const noexcept;
		std::string GetErrorString() const noexcept;
	private:
		HRESULT hr;
	};
private:
	class WindowClass
	{
	public:
		static const char* GetName() noexcept;
		static HINSTANCE GetInstance() noexcept;
	private:
		WindowClass() noexcept;
		~WindowClass();
		WindowClass(const WindowClass&) = delete;
		WindowClass& operator = (const WindowClass&) = delete;
		static constexpr const char* wndClassName = "DirectX Window";
		static WindowClass wndClass;
		HINSTANCE hInst;

	};
public:
	Window(int width, int height, const char* name);
	~Window();
	Window(const Window&) = delete;
	Window& operator = (const Window&) = delete;
	void SetWindowTitle(const std::string& title);
	static std::optional<int> ProcessMessages();
	double mouseX,mouseY;
	Renderer& Render();	
	KeyboardClass keyboard;
private:
	static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	static LRESULT CALLBACK HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
private:
	int width;
	int height;
	HWND hWnd;

	std::unique_ptr<Renderer> pRenderer;
};

//error exception helper macro
#define WND_EXCEPT(hr) Window::Exception( __LINE__, __FILE__, hr)
#define WND_PREVIOUS_EXCEPT(hr) Window::Exception( __LINE__, __FILE__, GetLastError())
