#pragma once
#include "Bindable.h"

class VertexShader : public Bindable
{
public:
	VertexShader(Renderer& render, const std::wstring& path);
	void Bind	(Renderer& render) noexcept override;
	ID3DBlob* GetBytecode() const noexcept;
protected:
	Microsoft::WRL::ComPtr<ID3DBlob> pBytecodeBlob;
	Microsoft::WRL::ComPtr<ID3D11VertexShader> pVertexShader;
};