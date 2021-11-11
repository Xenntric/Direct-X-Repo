#include "PixelShader.h"

PixelShader::PixelShader(Renderer& render, const std::wstring& path)
{

	Microsoft::WRL::ComPtr<ID3DBlob> pBlob;
	D3DReadFileToBlob(path.c_str(), &pBlob);
	GetDevice(render)->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pPixelShader);
}

void PixelShader::Bind(Renderer& render) noexcept
{
	GetContext(render)->PSSetShader(pPixelShader.Get(), nullptr, 0u);
}