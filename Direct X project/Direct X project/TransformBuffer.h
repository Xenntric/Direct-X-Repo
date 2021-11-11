#pragma once
#include "ConstantBuffer.h"
#include "Drawable.h"
#include <DirectXMath.h>

class TransformBuffer : public Bindable
{
public:
	TransformBuffer	(Renderer& render, const Drawable& parent);
	void Bind		(Renderer& render) noexcept override;
private:
	VertexConstantBuffer<DirectX::XMMATRIX> vcbuf;
	const Drawable& parent;
};