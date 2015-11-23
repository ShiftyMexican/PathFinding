/*!		Author: Jarrod Dowsey */
/*!		Description: Basic Vector3 math lib class*/


#ifndef VEC3_H
#define VEC3_H

#include "math.h"

class Vec3
{
public:

	/// Default Constructor
	Vec3();
	
	/// Overloaded Constructor
	Vec3(float X, float Y, float Z) : x(X), y(Y), z(Z){};
	
	/** \brief Operator overload for + operation
	*	\param Const Vec3 &rhs
	*	\return Vec3
	*/
	Vec3 operator + (const Vec3 &rhs) const;

	/** \brief Operator overload for += operation
	*	\param Const Vec3 &rhs
	*	\return Vec3
	*/
	Vec3& operator += (const Vec3 &rhs);
	
	/** \brief Operator overload for + operation
	*	\param float rhs
	*	\return Vec3
	*/
	Vec3 operator + ( float rhs) const;

	/** \brief Operator overload for += operation
	*	\param float rhs
	*	\return Vec3
	*/
	Vec3& operator += (float rhs);
	
	/** \brief Operator overload for - operation
	*	\param Const Vec3 &rhs
	*	\return Vec3
	*/
	Vec3 operator - (const Vec3 &rhs) const;

	/** \brief Operator overload for -= operation
	*	\param Const Vec3 &rhs
	*	\return Vec3
	*/
	Vec3& operator -= (const Vec3 &rhs);
	
	/** \brief Operator overload for - operation
	*	\param float rhs
	*	\return Vec3
	*/
	Vec3 operator - ( float rhs) const;

	/** \brief Operator overload for -= operation
	*	\param float rhs
	*	\return Vec3
	*/
	Vec3& operator -= ( float rhs);
	
	/** \brief Operator overload for * operation
	*	\param Const Vec3 &rhs
	*	\return Vec3
	*/
	Vec3 operator * (const Vec3 &rhs) const;

	/** \brief Operator overload for *= operation
	*	\param Const Vec3 &rhs
	*	\return Vec3
	*/
	Vec3& operator *= (const Vec3 &rhs);
	
	/** \brief Operator overload for * operation
	*	\param float rhs
	*	\return Vec3
	*/
	Vec3 operator * (const float &rhs) const;

	/** \brief Operator overload for *= operation
	*	\param float rhs
	*	\return Vec3
	*/
	Vec3& operator *= (const float &rhs);
	
	/** \brief Operator overload for / operation
	*	\param Const Vec3 &rhs
	*	\return Vec3
	*/
	Vec3 operator / (const Vec3 &rhs) const;

	/** \brief Operator overload for /= operation
	*	\param Const Vec3 &rhs
	*	\return Vec3
	*/
	Vec3& operator /= (const Vec3 &rhs);
	
	/** \brief Operator overload for / operation
	*	\param float rhs
	*	\return Vec3
	*/
	Vec3 operator / ( float rhs) const;

	/** \brief Operator overload for /= operation
	*	\param float rhs
	*	\return Vec3
	*/ 
	Vec3& operator /= (float rhs);
	
	/** \brief Operator overload for the dot product
	*	\param Vec3 a, Vec3 b
	*	\return float
	*/
	static float DotProduct(Vec3 a, Vec3 b);

	/// Length function
	float Len();

	/// Normalize function
	void Normalize();

	/// Variable for defining x
	float x; 

	/// Variable for defining y
	float y; 

	/// Variable for defining z
	float z; 

protected:
private:
};

#endif