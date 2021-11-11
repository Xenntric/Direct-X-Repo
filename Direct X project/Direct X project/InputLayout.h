#pragma once
#include "Bindable.h"

class InputLayout : public Bindable
{
public:
	InputLayout(Renderer& render,
		const std::vector<D3D11_INPUT_ELEMENT_DESC>& layout,
		ID3DBlob* pVertexShaderBytecode);
	void Bind(Renderer& render) noexcept override;
protected:
	Microsoft::WRL::ComPtr<ID3D11InputLayout> pInputLayout;
};