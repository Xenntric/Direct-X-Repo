#pragma once
#include <Windows.h>
#include <d3d11.h>

class Renderer
{
public:
	Renderer(HWND hWnd);
	Renderer(const Renderer&) = delete;
	Renderer& operator = (const Renderer&) = delete;
	~Renderer();
	
	void EndFrame();
	void ClearBuffer(float red, float green, float blue) noexcept
	{
		const float colour[] = { red, green, blue, 1.0f };
		pContext->ClearRenderTargetView(pTarget, colour);
	}

private:
	ID3D11Device* pDevice			= nullptr;
	IDXGISwapChain*	pSwap			= nullptr;
	ID3D11DeviceContext* pContext	= nullptr;
	ID3D11RenderTargetView* pTarget = nullptr;

};

