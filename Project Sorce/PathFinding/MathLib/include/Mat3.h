/*! Author: Jarrod Dowsey */
/*!	Description: Basic Matrix 3 class */


#ifndef MAT3_H
#define MAT3_H

#include "Vec2.h"

class Mat3
{
public:

	/// Union for Matrix
	union 
	{
		float m[9];
		float mm[3][3];

		struct 
		{
			float	m1, m2, m3,
					m4, m5, m6,
					m7, m8, m9;
		};
	};
	
	/// Default constructor
	Mat3();

	/// Overload Constructor
	Mat3(	float M1, float M2, float M3,
			float M4, float M5, float M6,
			float M7, float M8, float M9 );

	/// Creates the identity matix
	static Mat3 CreateIdentity();

	/// Creates a Translation matrix
	static Mat3 CreateTranslation(const Vec2& vec);

	/// Creates the scale for a matrix
	static Mat3 CreateScale(const Vec2& scale);

	/// Creates the rotation for a matrix
	static Mat3 CreateRotation( float rot);

	/// Converts a degrees value to a radian value
	static float ConvertToRadians(float degrees);

	void CopyFrom(const Mat3& src);

	/// Translate the matrix
	void Translate(const Vec2& vec);

	/// Rotate the matrix
	void Rotate(float angle);

	/// Rotation in degrees
	void RotateDegrees(float angle);

	/// Scale the matrix
	void Scale(const Vec2& scale);

	/// Set Translation of a matrix
	void SetTranslation(const Vec2& vec);

	/// Set the rotation of a matrix
	void SetRotation(float angle);

	/// Set the scale of a matrix
	void SetScale(float newScalex, float newScaley);

	/// Operator overload for the * operation
	Mat3 operator	*(const Mat3 &rhs	)const;

	/// Operator overload for the *= operation
	Mat3 &operator  *=(const Mat3 &rhs	);

	/// Gets the Translation
	Vec2 GetTranslation();

	/// Gets the Scale
	Vec2 GetScale();

	/// Gets the Up Rotation
	float GetUpRotation();

	/// Gets the Up Direction
	Vec2 GetUpDirection();

	/// Gets the Right Rotation
	float GetRightRotation();

	// Gets the Right Direction
	Vec2 GetRightDirection();

};

#endif