//------------------------------------------------------------------------------------
// TO DO: Proj3_scenemanip
// New functions
// No implementation required
//-----------------------------------------------------------------------------------



// STVector3.inl
#ifndef __STVECTOR3_INL__
#define __STVECTOR3_INL__

/**
* Inline file for STVector3.h
*/

#include "STPoint3.h"
#include "STUtil.h" // for STMin, STMax
#include "STMatrix4.h"

//

inline STVector3::STVector3()
{
    x = 0;
    y = 0;
    z = 0;
}

inline STVector3::STVector3(float inX, float inY, float inZ)
{
    x = inX;
    y = inY;
    z = inZ;
}

inline STVector3::STVector3(float s)
{
    x = s;
    y = s;
    z = s;
}

inline STVector3::STVector3(const STVector3 &v)
{
    x = v.x;
    y = v.y;
    z = v.z;
}

inline STVector3::STVector3(const STPoint3& p)
{
    x = p.x;
    y = p.y;
    z = p.z;
}

inline STVector3& STVector3::operator=(const STVector3 &v)
{
    x = v.x;
    y = v.y;
    z = v.z;
    return *this;
}

/**
* Length of vector
*/
inline float STVector3::Length() const
{
    return sqrtf(LengthSq());
}

/**
* Length squared of vector
*/
inline float STVector3::LengthSq() const
{
    return x * x + y * y + z * z;
}

/**
* True if all elements are real values
*/
inline bool STVector3::Valid() const
{
    // For standard floating-point math, the
    // "not-a-number" (NaN) representation
    // will test as not-equal to every value,
    // including itself!
    return ((x == x) && (y == y) && (z == z));
}


inline void STVector3::Normal(const STVector3 &v)
{
	float oneOlength = 1.f/sqrtf( (v.x * v.x) + (v.y * v.y) + (v.z * v.z) );
	//float oneOlength = InvSqrt_Lomont( (v.x * v.x) + (v.y * v.y) + (v.z * v.z) );

	x = v.x * oneOlength;
	y = v.y * oneOlength;
	z = v.z * oneOlength;
}


/**
* Sets the length of vector to 1
*/
inline void STVector3::Normalize()
{
    float len = Length();
    if (len != 0.0f) {
        (*this) /= len;
    }
}


inline void STVector3::Normalize(const STVector3 &v)
{
	float oneOlength = 1.f/sqrtf( (v.x * v.x) + (v.y * v.y) + (v.z * v.z) );
	//float oneOlength = InvSqrt_Lomont( (v.x * v.x) + (v.y * v.y) + (v.z * v.z) );

	x = v.x * oneOlength;
	y = v.y * oneOlength;
	z = v.z * oneOlength;
}

/**
* Sets the length of vector to NewLength
*/
inline void STVector3::SetLength(float newLength)
{
    float len = Length();
    if (len != 0.0f) {
        (*this) *= newLength / len;
    }
}

/**
* Returns cross product of two vectors
*/
inline STVector3 STVector3::Cross(
    const STVector3& left, const STVector3& right)
{
    return STVector3(left.y * right.z - left.z * right.y,
                     left.z * right.x - left.x * right.z,
                     left.x * right.y - left.y * right.x);
}

/**
* Returns dot product of two vectors
*/
inline float STVector3::Dot(
    const STVector3& left, const STVector3& right)
{
    return left.x * right.x + left.y * right.y + left.z * right.z;
}

/**
* Returns direct product of two vectors
*/
inline STVector3 STVector3::DirectProduct(
    const STVector3& left, const STVector3& right)
{
    return STVector3(left.x * right.x, left.y * right.y, left.z * right.z);
}

/**
* Linearly interpolates between two vectors;
* s = 0 returns left, s = 1 returns right
*/
inline STVector3 STVector3::Lerp(
    const STVector3& left, const STVector3& right, float s)
{
    return left + s * (right - left);
}

/**
* Returns the vector that is the component-wise maximum of the given vectors
*/
inline STVector3 STVector3::ComponentMax(
    const STVector3& left, const STVector3& right)
{
    return STVector3(
        STMax(left.x, right.x),
        STMax(left.y, right.y),
        STMax(left.z, right.z));
}

/**
* Returns the vector that is the component-wise minimum of the given vectors
*/
inline STVector3 STVector3::ComponentMin(
    const STVector3& left, const STVector3& right)
{
    return STVector3(
        STMin(left.x, right.x),
        STMin(left.y, right.y),
        STMin(left.z, right.z));
}

inline STVector3 operator*(const STVector3& left, float right)
{
    STVector3 result(left);
    result *= right;
    return result;
}

inline STVector3 operator*(float left, const STVector3& right)
{
    STVector3 result(right);
    result *= left;
    return result;
}

inline void STVector3::Transform(const STMatrix4 &matrix )
{
    STVector3 out;

    out.x = x * matrix.table[0][0] + y * matrix.table[1][0] + z * matrix.table[2][0];
    out.y = x * matrix.table[0][1] + y * matrix.table[1][1] + z * matrix.table[2][1];
    out.z = x * matrix.table[0][2] + y * matrix.table[1][2] + z * matrix.table[2][2];

    x = out.x;
    y = out.y;
    z = out.z;
}


inline STVector3 operator/(const STVector3& left, float right)
{
    STVector3 result(left);
    result /= right;
    return result;
}

inline STVector3 operator+(const STVector3& left, const STVector3& right)
{
    STVector3 result(left);
    result += right;
    return result;
}

inline STVector3 operator-(const STVector3& left, const STVector3& right)
{
    STVector3 result(left);
    result -= right;
    return result;
}

inline STVector3& STVector3::operator*=(float right)
{
    x *= right;
    y *= right;
    z *= right;
    return *this;
}

inline STVector3& STVector3::operator/=(float right)
{
    x /= right;
    y /= right;
    z /= right;
    return *this;
}

inline STVector3& STVector3::operator+=(const STVector3& right)
{
    x += right.x;
    y += right.y;
    z += right.z;
    return *this;
}

inline STVector3& STVector3::operator-=(const STVector3& right)
{
    x -= right.x;
    y -= right.y;
    z -= right.z;
    return *this;
}

inline STVector3 operator-(const STVector3& v)
{
    return STVector3(-v.x, -v.y, -v.z);
}

inline STVector3 operator-(const STPoint3& left, const STPoint3& right)
{
    return STVector3(left.x - right.x,
                     left.y - right.y,
                     left.z - right.z);
}

#endif  // __STVECTOR3_INL__
