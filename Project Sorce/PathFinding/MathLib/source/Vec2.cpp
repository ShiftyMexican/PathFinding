#include "MathLib.h"
#include "Math.h"

// Default Constructor
Vec2::Vec2()
{
	x = 0;
	y = 0;
}

//-----------------------------------------------------
// + overload
Vec2 Vec2::operator + (const Vec2 &rhs) const
{
	return Vec2( x + rhs.x, y + rhs.y);
}

Vec2& Vec2::operator += (const Vec2 &rhs)
{
	x += rhs.x;
	y += rhs.y;

	return *this;
}

//-----------------------------------------------------
// + overload
Vec2 Vec2::operator + ( float rhs) const
{
	return Vec2( x + rhs, y + rhs);
}

Vec2& Vec2::operator += (float rhs)
{
	x += rhs;
	y += rhs;

	return *this;
}

//-----------------------------------------------------
// - overload
Vec2 Vec2::operator - (const Vec2 &rhs) const
{
	return Vec2( x - rhs.x, y - rhs.y);
}

Vec2& Vec2::operator -= (const Vec2 &rhs)
{
	x -= rhs.x;
	y -= rhs.y;

	return *this;
}

//-----------------------------------------------------
// - overload
Vec2 Vec2::operator - ( float rhs) const
{
	return Vec2( x - rhs, y - rhs);
}

Vec2& Vec2::operator -= ( float rhs)
{
	x -= rhs;
	y -= rhs;

	return *this;
}

//-----------------------------------------------------
// * overload
Vec2 Vec2::operator * (const Vec2 &rhs) const
{
	return Vec2( x * rhs.x, y * rhs.y);
}

Vec2& Vec2::operator *= (const Vec2 &rhs)
{
	x *= rhs.x;
	y *= rhs.y;

	return *this;
}

Vec2 Vec2::operator * (const Mat3 &rhs) const
{
	return Vec2((x*rhs.m1)+(y*rhs.m4) + rhs.m7,(x*rhs.m2)+(y*rhs.m5)+ rhs.m8);
}

//-----------------------------------------------------
// * overload
Vec2 Vec2::operator * (const float &rhs) const
{
	return Vec2( x * rhs, y * rhs);
}

Vec2& Vec2::operator *= (const float &rhs)
{
	x *= rhs;
	y *= rhs;

	return *this;
}

//-----------------------------------------------------
// / operator
Vec2 Vec2::operator / (const Vec2 &rhs) const
{
	return Vec2( x / rhs.x, y / rhs.y);
}

Vec2& Vec2::operator /= (const Vec2 &rhs)
{
	x /= rhs.x;
	y /= rhs.y;

	return *this;
}

//-----------------------------------------------------
// / operator
Vec2 Vec2::operator / ( float rhs) const
{
	return Vec2( x / rhs, y / rhs);
}

Vec2& Vec2::operator /= (float rhs)
{
	x /= rhs;
	y /= rhs;

	return *this;
}

//-----------------------------------------------------
// Getting perpendicular clockwise
Vec2 Vec2::GetPerpCW()
{
	return Vec2 (y, -x);
}

// Getting perpendicular Anit Clockwise
Vec2 Vec2::GetPerpACW()
{
	return Vec2 (-y, x);
}

// Dot Product
float Vec2::DotProduct(Vec2 a, Vec2 b)
{
	return (a.x * b.x) + (a.y * b.y);
}

// Length function
float Vec2::Len()
{
	return sqrt(x*x + y*y);
}

// Normalize function
void Vec2::Normalize()
{

	float len = Len();
	if( len == 0 )
		return;

	x /= len;
	y /= len;
}