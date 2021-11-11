#pragma once
#include "Bindable.h"

class PixelShader : public Bindable
{
public:
	PixelShader	(Renderer& render, const std::wstring& path);
	void Bind	(Renderer& render) noexcept override;
protected:
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pPixelShader;
};