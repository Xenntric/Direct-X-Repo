#include "Topology.h"

Topology::Topology(Renderer& render, D3D11_PRIMITIVE_TOPOLOGY type)
	:
	type(type)
{}

void Topology::Bind(Renderer& render) noexcept
{
	GetContext(render)->IASetPrimitiveTopology(type);
}