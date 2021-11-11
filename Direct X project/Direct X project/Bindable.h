#pragma once
#include "Renderer.h"

class Bindable
{
public:
	virtual void Bind(Renderer& render) noexcept = 0;
	virtual ~Bindable() = default;
protected:
	static ID3D11DeviceContext* GetContext(Renderer& render) noexcept;
	static ID3D11Device* GetDevice(Renderer& render) noexcept;
};

