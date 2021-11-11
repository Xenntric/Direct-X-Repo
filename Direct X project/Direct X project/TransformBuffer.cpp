#include "TransformBuffer.h"


TransformBuffer::TransformBuffer(Renderer& render, const Drawable& parent)
	:
	vcbuf(render),
	parent(parent)
{}

void TransformBuffer::Bind(Renderer& render) noexcept
{
	vcbuf.Update(render,
		DirectX::XMMatrixTranspose(
			parent.GetTransformXM() * render.GetProjection()
		)
	);
	vcbuf.Bind(render);
}
