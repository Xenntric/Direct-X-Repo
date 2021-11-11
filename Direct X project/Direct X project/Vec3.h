#pragma once
#include <cmath>

class Vec3
{
public:
	Vec3();
	Vec3(float x_, float y_, float z_);

	void Add(Vec3 a, Vec3 b);

	void Subtract(Vec3 a, Vec3 b);

	void ScalarMultiplication(Vec3 a, float s);

	float Mag();

	void Normalize();

	float Dot(Vec3 a, Vec3 b);

	void Lerp(Vec3 a, Vec3 b, float time);

	void RotateZ(float angle);

	float x;
	float y;
	float z;
};