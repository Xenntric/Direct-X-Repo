#include "InputLayout.h"

InputLayout::InputLayout(Renderer& render,
	const std::vector<D3D11_INPUT_ELEMENT_DESC>& layout,
	ID3DBlob* pVertexShaderBytecode)
{

	GetDevice(render)->CreateInputLayout(
		layout.data(), (UINT)layout.size(),
		pVertexShaderBytecode->GetBufferPointer(),
		pVertexShaderBytecode->GetBufferSize(),
		&pInputLayout
	);
}

void InputLayout::Bind(Renderer& render) noexcept
{
	GetContext(render)->IASetInputLayout(pInputLayout.Get());
}