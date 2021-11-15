#include "Vec3.h"

/* Vec3 Constructor
	Set the vector's x, y, and z components to the parameters supplied*/
Vec3::Vec3(float x_, float y_, float z_)
{
	x = x_;
	y = y_;
	z = z_;
}

/* Add Member Function
	Adds the vector's x, y, and z components with the supplied vector's x, y, and z components */
void Vec3::Add(Vec3 a, Vec3 b)
{
	a.x = a.x + b.x;
	a.y = a.y + b.y;
	a.z = a.z + b.z;
}

/* Subtract Member Function
	Subtracts the vector's x, y, and z components with the parameters supplied */
void Vec3::Subtract(Vec3 a, Vec3 b)
{
	a.x = a.x - b.x;
	a.y = a.y - b.y;
	a.z = a.z - b.z;
}

/* ScalarMultiplication Member Function
	Multiplies the vector's x, y, and z components with the scalar supplied */
void Vec3::ScalarMultiplication(Vec3 a, float s)
{
	a.x = a.x * s;
	a.y = a.y * s;
	a.z = a.z * s;
}

/* Mag Member Function
	Calculates and returns the vector's magnitude */
float Vec3::Mag()
{
	double mag = sqrt(pow(x,2) + pow(y, 2) + pow(z, 2));
	return mag;
}

/* Normalize Member Function
	Normalizes the vector */
void Vec3::Normalize()
{
	double mag = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
	x = x / mag;
	y = y / mag;
	z = z / mag;
}

/* Dot Member Function
	Calculates and returns the scalar result for the dot product of the vector and vector supplied */
float Vec3::Dot(Vec3 a, Vec3 b)
{
	double dot = ((a.x * b.x) + (a.y * b.y) + (a.z * b.z));
	return dot;
}

/* Lerp Member Function
	Calculates the lerp for the vector and vector supplied using unit interval t */
void Vec3::Lerp(Vec3 a, Vec3 b, float time)
{
	a.x = ((b.x - time) * b.x + time	* b.x);
	a.y = ((b.y - time) * b.y + time	* b.y);
	a.z = ((b.z - time) * b.z + time	* b.z);
}

/* RotateZ Member Function
	Calculates the rotation for the vector */
void Vec3::RotateZ(float angle)
{
	x = x * cos(90) - y * sin(90);
	y = x * sin(90) + y * cos(90);
}