#include "Bindable.h"

ID3D11DeviceContext* Bindable::GetContext(Renderer& render) noexcept
{
	return render.pContext.Get();
}

ID3D11Device* Bindable::GetDevice(Renderer& render) noexcept
{
	return render.pDevice.Get();
}
