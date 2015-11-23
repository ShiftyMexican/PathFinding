#include "MathLib.h"
#include "math.h"

// Default Constructor
Vec3::Vec3()
{
	x = 0;
	y = 0;
	z = 0;
}

//--------------------------------------------------------
// + overload
Vec3 Vec3::operator + (const Vec3 &rhs) const
{
	return Vec3( x + rhs.x, y + rhs.y, z +rhs.z);
}

Vec3& Vec3::operator += (const Vec3 &rhs)
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;

	return *this;
}
//-----------------------------------------------------
// + overload
Vec3 Vec3::operator + ( float rhs) const
{
	return Vec3( x + rhs, y + rhs, z + rhs);
}

Vec3& Vec3::operator += (float rhs)
{
	x += rhs;
	y += rhs;
	z += rhs;

	return *this;
}
//-----------------------------------------------------
// - overload
Vec3 Vec3::operator - (const Vec3 &rhs) const
{
	return Vec3( x - rhs.x, y - rhs.y, z - rhs.z);
}

Vec3& Vec3::operator -= (const Vec3 &rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;

	return *this;
}
//-----------------------------------------------------
// - overload
Vec3 Vec3::operator - ( float rhs) const
{
	return Vec3( x - rhs, y - rhs, z - rhs);
}

Vec3& Vec3::operator -= ( float rhs)
{
	x -= rhs;
	y -= rhs;
	z -= rhs;

	return *this;
}
//-----------------------------------------------------
// * overload
Vec3 Vec3::operator * (const Vec3 &rhs) const
{
	return Vec3( x * rhs.x, y * rhs.y, z * rhs.z);
}

Vec3& Vec3::operator *= (const Vec3 &rhs)
{
	x *= rhs.x;
	y *= rhs.y;
	z *= rhs.z;

	return *this;
}
//-----------------------------------------------------
// * overload
Vec3 Vec3::operator * (const float &rhs) const
{
	return Vec3( x * rhs, y * rhs, z * rhs);
}

Vec3& Vec3::operator *= (const float &rhs)
{
	x *= rhs;
	y *= rhs;
	z *= rhs;

	return *this;
}
//-----------------------------------------------------
// / operator
Vec3 Vec3::operator / (const Vec3 &rhs) const
{
	return Vec3( x / rhs.x, y / rhs.y, z / rhs.z);
}

Vec3& Vec3::operator /= (const Vec3 &rhs)
{
	x /= rhs.x;
	y /= rhs.y;
	z /= rhs.z;

	return *this;
}
//-----------------------------------------------------
// / operator
Vec3 Vec3::operator / ( float rhs) const
{
	return Vec3( x / rhs, y / rhs, z / rhs);
}

Vec3& Vec3::operator /= (float rhs)
{
	x /= rhs;
	y /= rhs;
	z /= rhs;

	return *this;
}
//-----------------------------------------------------
float Vec3::DotProduct(Vec3 a, Vec3 b)
{
	return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

// Length function
float Vec3::Len()
{
	return sqrt(x*x + y*y + z*z);
}

// Normalize function
void Vec3::Normalize()
{
	float len = Len();
	x/= len;
	y/= len;
	z/= len;
}