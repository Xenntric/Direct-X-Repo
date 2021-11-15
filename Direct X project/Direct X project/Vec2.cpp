#include "Vec2.h"

/* Vec3 Constructor
	Set the vector's x, y, and z components to the parameters supplied*/
Vec2::Vec2(float x_, float y_)
{
	x = x_;
	y = y_;
}

/* Add Member Function
	Adds the vector's x, y, and z components with the supplied vector's x, y, and z components */
void Vec2::Add(Vec2 a, Vec2 b)
{
	a.x = a.x + b.x;
	a.y = a.y + b.y;
}

/* Subtract Member Function
	Subtracts the vector's x, y, and z components with the parameters supplied */
void Vec2::Subtract(Vec2 a, Vec2 b)
{
	a.x = a.x - b.x;
	a.y = a.y - b.y;
}

/* ScalarMultiplication Member Function
	Multiplies the vector's x, y, and z components with the scalar supplied */
void Vec2::ScalarMultiplication(Vec2 a, float s)
{
	a.x = a.x * s;
	a.y = a.y * s;
}

/* Mag Member Function
	Calculates and returns the vector's magnitude */
float Vec2::Mag()
{
	double mag = sqrt(pow(x, 2) + pow(y, 2));
	return mag;
}

/* Normalize Member Function
	Normalizes the vector */
void Vec2::Normalize()
{
	double mag = sqrt(pow(x, 2) + pow(y, 2));
	x = x / mag;
	y = y / mag;
}

/* Dot Member Function
	Calculates and returns the scalar result for the dot product of the vector and vector supplied */
float Vec2::Dot(Vec2 a, Vec2 b)
{
	double dot = ((a.x * b.x) + (a.y * b.y));
	return dot;
}

/* Lerp Member Function
	Calculates the lerp for the vector and vector supplied using unit interval t */
void Vec2::Lerp(Vec2 a, Vec2 b, float time)
{
	a.x = ((b.x - time) * b.x + time * b.x);
	a.y = ((b.y - time) * b.y + time * b.y);
}

/* RotateZ Member Function
	Calculates the rotation for the vector */
void Vec2::RotateZ(float angle)
{
	x = x * cos(90) - y * sin(90);
	y = x * sin(90) + y * cos(90);
}