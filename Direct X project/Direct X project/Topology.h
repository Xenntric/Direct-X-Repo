#pragma once
#include "Bindable.h"

class Topology : public Bindable
{
public:
	Topology	(Renderer&render, D3D11_PRIMITIVE_TOPOLOGY type);
	void Bind	(Renderer&render) noexcept override;
protected:
	D3D11_PRIMITIVE_TOPOLOGY type;
};