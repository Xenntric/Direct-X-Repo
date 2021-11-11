#pragma once
#include "Bindable.h"

template<typename C>
class ConstantBuffer : public Bindable
{
public:
	void Update(Renderer& render, const C& consts)
	{

		D3D11_MAPPED_SUBRESOURCE msr;
		GetContext(render)->Map(
			pConstantBuffer.Get(), 0u,
			D3D11_MAP_WRITE_DISCARD, 0u,
			&msr
		);

		memcpy(msr.pData, &consts, sizeof(consts));
		GetContext(render)->Unmap(pConstantBuffer.Get(), 0u);
	}
	ConstantBuffer(Renderer& render, const C& consts)
	{
		D3D11_BUFFER_DESC cbd;
		cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cbd.Usage = D3D11_USAGE_DYNAMIC;
		cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		cbd.MiscFlags = 0u;
		cbd.ByteWidth = sizeof(consts);
		cbd.StructureByteStride = 0u;

		D3D11_SUBRESOURCE_DATA csd = {};
		csd.pSysMem = &consts;
		GetDevice(render)->CreateBuffer(&cbd, &csd, &pConstantBuffer);
	}
	ConstantBuffer(Renderer& render)
	{

		D3D11_BUFFER_DESC cbd;
		cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cbd.Usage = D3D11_USAGE_DYNAMIC;
		cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		cbd.MiscFlags = 0u;
		cbd.ByteWidth = sizeof(C);
		cbd.StructureByteStride = 0u;
		GetDevice(render)->CreateBuffer(&cbd, nullptr, &pConstantBuffer);
	}
protected:
	Microsoft::WRL::ComPtr<ID3D11Buffer> pConstantBuffer;
};

template<typename C>
class VertexConstantBuffer : public ConstantBuffer<C>
{
	using ConstantBuffer<C>::pConstantBuffer;
	using Bindable::GetContext;
public:
	using ConstantBuffer<C>::ConstantBuffer;
	void Bind(Renderer& render) noexcept override
	{
		GetContext(render)->VSSetConstantBuffers(0u, 1u, pConstantBuffer.GetAddressOf());
	}
};

template<typename C>
class PixelConstantBuffer : public ConstantBuffer<C>
{
	using ConstantBuffer<C>::pConstantBuffer;
	using Bindable::GetContext;
public:
	using ConstantBuffer<C>::ConstantBuffer;
	void Bind(Renderer& render) noexcept override
	{
		GetContext(render)->PSSetConstantBuffers(0u, 1u, pConstantBuffer.GetAddressOf());
	}
};