#include "VertexBuffer.h"

void VertexBuffer::Bind(Renderer& render) noexcept
{
	const UINT offset = 0u;
	GetContext(render)->IASetVertexBuffers(0u, 1u, pVertexBuffer.GetAddressOf(), &stride, &offset);
}