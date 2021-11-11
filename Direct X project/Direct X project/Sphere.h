#pragma once
#include "Drawable.h"

#define _USE_MATH_DEFINES

#include<cmath>

#include<ioStream>


class Sphere : public Drawable
{
public:
	Sphere(Renderer& render, float x, float y, float z, float radius, int sliceCount, int stackCount);

	void Update(float dt) noexcept override;

	DirectX::XMMATRIX GetTransformXM() const noexcept override;


private:
	//math constants
	const double pi = 3.14159265358979323846; 

	//construction
	int sliceCount, stackCount;
	float radius;
		//resolution of sphere
	float phiStep;
	float thetaStep;

	//worldspace positions
	float x, y, z;

	// positional
	float r;
	float roll = 0.0f;
	float pitch = 0.0f;
	float yaw = 0.0f;
	float theta;
	float phi;
	float chi;
	// speed (delta/s)
	float droll;
	float dpitch;
	float dyaw;
	float dtheta;
	float dphi;
	float dchi;
};
