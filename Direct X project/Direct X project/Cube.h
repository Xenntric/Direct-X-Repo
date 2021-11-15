#pragma once
#include "DrawableBase.h"

class Cube : public DrawableBase<Cube>
{
public:
	Cube(Renderer& render, float x, float y, float z);
	void Update(float dt) noexcept override;

	//DirectX::XMMATRIX SetTransformXM() noexcept;
	DirectX::XMMATRIX GetTransformXM() const noexcept override;

private:
	//worldspace positions
	float x, y, z;
	
	float r;
	float roll = 0.0f;
	float pitch = 0.0f;
	float yaw = 0.0f;
	float theta;
	float phi;
	float chi;



	// speed (delta/s)
	
	//rotation about shape centre
	float droll;
	float dpitch;
	float dyaw;
	//rotation about world origin
	float dtheta;
	float dphi;
	float dchi;
};
