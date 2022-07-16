#pragma once
#include "Renderer.h"
#include "Vec3.h"
class Camera
{
public:

	DirectX::XMMATRIX GetMatrix() const noexcept;
	void reset();

private:

	float distFromOrigin	= 20.0f;
	float theta				= 0.0f;
	float phi				= 0.0f;
	float pitch				= 0.0f;
	float yaw				= 0.0f;
	float roll				= 0.0f;
};

