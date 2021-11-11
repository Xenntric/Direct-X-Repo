#pragma once
#include "Bindable.h"

class IndexBuffer : public Bindable
{
public:
	IndexBuffer(Renderer& render, const std::vector<unsigned short>& indices);
	void Bind(Renderer& render) noexcept override;
	UINT GetCount() const noexcept;
protected:
	UINT count;
	Microsoft::WRL::ComPtr<ID3D11Buffer> pIndexBuffer;
};