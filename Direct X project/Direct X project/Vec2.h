#pragma once
#include <cmath>

class Vec2
{
public:
	Vec2();
	Vec2(float x_, float y_);

	void Add(Vec2 a, Vec2 b);

	void Subtract(Vec2 a, Vec2 b);

	void ScalarMultiplication(Vec2 a, float s);

	float Mag();

	void Normalize();

	float Dot(Vec2 a, Vec2 b);
				
	void Lerp(Vec2 a, Vec2 b, float time);

	void RotateZ(float angle);

	float x;
	float y;
	float z;
};