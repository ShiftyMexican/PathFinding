/*! Author: Jarrod Dowsey */
/*!	Description: Basic Vector2 math lib class */


#ifndef VEC2_H
#define VEC2_H

#include "math.h"

class Mat3;

class Vec2
{
public:

	/// Default Constructor
	Vec2();

	/// overloaded constructor
	Vec2(float X, float Y) : x(X), y(Y) {};
	
	/** \brief Operator overload for + operation
	*	\param Const Vec2 &rhs
	*	\return Vec2
	*/
	Vec2 operator + (const Vec2 &rhs) const;

	/** \brief Operator overload for += operation
	*	\param Const Vec2 &rhs
	*	\return Vec2
	*/
	Vec2& operator += (const Vec2 &rhs);

	/** \brief Operator overload for + operation
	*	\param float rhs
	*	\return Vec2
	*/
	Vec2 operator + ( float rhs) const;

	/** \brief Operator overload for += operation
	*	\param float rhs
	*	\return Vec2
	*/
	Vec2& operator += (float rhs);

	/** \brief Operator overload for - operation
	*	\param Const Vec2 &rhs
	*	\return Vec2
	*/
	Vec2 operator - (const Vec2 &rhs) const;

	/** \brief Operator overload for -= operation
	*	\param Const Vec2 &rhs
	*	\return Vec2
	*/
	Vec2& operator -= (const Vec2 &rhs);

	/** \brief Operator overload for - operation
	*	\param float rhs
	*	\return Vec2
	*/
	Vec2 operator - ( float rhs) const;

	/** \brief Operator overload for -= operation
	*	\param float rhs
	*	\return Vec2
	*/
	Vec2& operator -= ( float rhs);

	/** \brief Operator overload for * operation
	*	\param Const Vec2 &rhs
	*	\return Vec2
	*/
	Vec2 operator * (const Vec2 &rhs) const;

	/** \brief Operator overload for *= operation
	*	\param Const Vec2 &rhs
	*	\return Vec2
	*/
	Vec2& operator *= (const Vec2 &rhs);
	Vec2 operator * (const Mat3 &rhs) const;
	
	/** \brief Operator overload for * operation
	*	\param float rhs
	*	\return Vec2
	*/
	Vec2 operator * (const float &rhs) const;

	/** \brief Operator overload for *= operation
	*	\param float rhs
	*	\return Vec2
	*/
	Vec2& operator *= (const float &rhs);

	/** \brief Operator overload for / operation
	*	\param Const Vec2 &rhs
	*	\return Vec2
	*/
	Vec2 operator / (const Vec2 &rhs) const;

	/** \brief Operator overload for /= operation
	*	\param Const Vec2 &rhs
	*	\return Vec2
	*/
	Vec2& operator /= (const Vec2 &rhs);

	/** \brief Operator overload for / operation
	*	\param float rhs
	*	\return Vec2
	*/
	Vec2 operator / ( float rhs) const;

	/** \brief Operator overload for /= operation
	*	\param float rhs
	*	\return Vec2
	*/
	Vec2& operator /= (float rhs);

	/// Getting perpendicular clockwise
	Vec2 GetPerpCW();

	/// Getting perpendicular Anit Clockwise
	Vec2 GetPerpACW();

	/// Dot Product
	float DotProduct(Vec2 a, Vec2 b);

	/// Length function
	float Len();

	/// Normalize function
	void Normalize();

	/// Variable to define x
	float x; 

	/// Variable to define y
	float y; 

protected:
private:
};


#endif
