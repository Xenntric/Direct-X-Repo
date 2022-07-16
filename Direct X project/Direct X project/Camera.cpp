#include "Camera.h"

DirectX::XMMATRIX Camera::GetMatrix() const noexcept
{
	const auto pos = DirectX::XMVector3Transform(
		DirectX::XMVectorSet(0.0f, 0.0f, -distFromOrigin, 0.0f),
		DirectX::XMMatrixRotationRollPitchYaw(phi, -theta, 0.0f));
	return DirectX::XMMatrixLookAtLH(pos, DirectX::XMVectorZero(),
		DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)) *
		DirectX::XMMatrixRotationRollPitchYaw(pitch, -yaw, roll);
}

void Camera::reset()
{
	distFromOrigin = 20.0f;
	theta = 0.0f;
	phi = 0.0f;
	pitch = 0.0f;
	yaw = 0.0f;
	roll = 0.0f;
}
