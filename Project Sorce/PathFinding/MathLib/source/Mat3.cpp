#include "Mat3.h"
#include "Vec2.h"
#include "Vec3.h"
#include <math.h>

Mat3::Mat3()
{
	m1 = 1, m2 = 0, m3 = 0,
	m4 = 0, m5 = 1, m6 = 0,
	m7 = 0, m8 = 0, m9 = 1;
}


Mat3::Mat3(	float M1, float M2, float M3,
			float M4, float M5, float M6,
			float M7, float M8, float M9 )
{
	m1 = M1; m2 = M2; m3 = M3;
	m4 = M4; m5 = M5; m6 = M6;
	m7 = M7; m8 = M8; m9 = M9;
}

Mat3 Mat3::operator *(const Mat3 &rhs) const 
{
	Mat3 mat;
	
	// Row 1
	mat.m1 = Vec3::DotProduct(Vec3(m1, m2, m3), Vec3(rhs.m1, rhs.m4, rhs.m7));
	mat.m2 = Vec3::DotProduct(Vec3(m1, m2, m3), Vec3(rhs.m2, rhs.m5, rhs.m8));
	mat.m3 = Vec3::DotProduct(Vec3(m1, m2, m3), Vec3(rhs.m3, rhs.m6, rhs.m9));
	
	//Row 2
	mat.m4 = Vec3::DotProduct(Vec3(m4, m5, m6), Vec3(rhs.m1, rhs.m4, rhs.m7));
	mat.m5 = Vec3::DotProduct(Vec3(m4, m5, m6), Vec3(rhs.m2, rhs.m5, rhs.m8));
	mat.m6 = Vec3::DotProduct(Vec3(m4, m5, m6), Vec3(rhs.m3, rhs.m6, rhs.m9));
	
	//Row 3
	mat.m7 = Vec3::DotProduct(Vec3(m7, m8, m9), Vec3(rhs.m1, rhs.m4, rhs.m7));
	mat.m8 = Vec3::DotProduct(Vec3(m7, m8, m9), Vec3(rhs.m2, rhs.m5, rhs.m8));
	mat.m9 = Vec3::DotProduct(Vec3(m7, m8, m9), Vec3(rhs.m3, rhs.m6, rhs.m9));

	return mat;
}

Mat3& Mat3::operator *=(const Mat3 &rhs)
{
	return *this = *this * rhs;
}

Mat3 Mat3::CreateIdentity()
{
	return Mat3(1, 0, 0, 0, 1, 0, 0, 0, 1);
}

Mat3 Mat3::CreateTranslation(const Vec2& vec)
{
	return Mat3(1.0f,0.0f,0.0f,
				0.0f,1.0f,0.0f,
				vec.x, vec.y, 1.0f);
}

Mat3 Mat3::CreateScale(const Vec2& scale)
{
	return Mat3(scale.x, 0.0f,		0.0f,
				0.0f,	 scale.y ,	0.0f,
				0.0f,	 0.0f,		1.0f);
}

float Mat3::ConvertToRadians(float degrees)
{
	return degrees / 57.2957795f;
}

Mat3 Mat3::CreateRotation(float rot)
{
	return Mat3(cosf(rot), -sinf(rot), 0,
				sinf(rot),  cosf(rot), 0,
				0,          0,         1);

}

void Mat3::CopyFrom(const Mat3 &src)
{
	for(int i = 0; i < 9; i++)
	{
		m[i] = src.m[i];
	}
}

void Mat3::SetTranslation(const Vec2& vec)
{
	m7 = vec.x;
	m8 = vec.y;
}

void Mat3::SetRotation(float angle)
{
	m1 = cosf(angle); m2 = -sinf(angle);
	m4 = sinf(angle); m5 = cosf(angle);
}

void Mat3::SetScale(float newScalex, float newScaley)
{
	Vec2 newScale;

	Vec2 Scale = GetScale();
	m1 = (m1/Scale.x) * newScalex;
	m2 = (m2/Scale.x) * newScalex;
	m4 = (m4/Scale.y) * newScaley;
	m5 = (m5/Scale.y) * newScaley;
}

Vec2 Mat3::GetTranslation()
{
	return Vec2(m7, m8);
}

Vec2 Mat3::GetScale()
{
	Vec2 xAxis(m1, m2);
	float xScale = xAxis.Len();
	Vec2 yAxis(m4, m5);
	float yScale = yAxis.Len();

	return Vec2(xScale, yScale);
}

float Mat3::GetUpRotation()
{
	Vec2 dir = GetUpDirection();
	return -atan2f(dir.y, dir.x);
}

Vec2 Mat3::GetUpDirection()
{
	Vec2 dir = Vec2(m4, m5);
	dir.Normalize();
	return dir;
}

float Mat3::GetRightRotation()
{
	Vec2 dir = GetRightDirection();
	return -atan2f(dir.y, dir.x);
}

Vec2 Mat3::GetRightDirection()
{
	Vec2 dir = Vec2(m1, m2);
	dir.Normalize();
	return dir;
}

void Mat3::Translate(const Vec2& vec)
{
	*this *= CreateTranslation(vec);
}

void Mat3::Rotate(float angle)
{
	*this = CreateRotation(angle) * *this;
}

void Mat3::RotateDegrees(float angle)
{
	Rotate(ConvertToRadians(angle));
}

void Mat3::Scale(const Vec2& scale)
{
	*this *= CreateScale(scale);
}
