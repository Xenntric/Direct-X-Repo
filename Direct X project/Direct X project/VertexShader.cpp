#include "VertexShader.h"

VertexShader::VertexShader(Renderer& render, const std::wstring& path)
{
	

	D3DReadFileToBlob(path.c_str(), &pBytecodeBlob);
	GetDevice(render)->CreateVertexShader(
		pBytecodeBlob->GetBufferPointer(),
		pBytecodeBlob->GetBufferSize(),
		nullptr,
		&pVertexShader);
}

void VertexShader::Bind(Renderer& render) noexcept
{
	GetContext(render)->VSSetShader(pVertexShader.Get(), nullptr, 0u);
}

ID3DBlob* VertexShader::GetBytecode() const noexcept
{
	return pBytecodeBlob.Get();
}