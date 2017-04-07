// STPoint3.h
#ifndef __STPOINT3_H__
#define __STPOINT3_H__

#include "stForward.h"

#include <math.h>
#include <iostream>

/**
*  Simple struct to represent 3D points
*/
struct STPoint3
{
    inline STPoint3();
    inline STPoint3(const float x, const float y, const float z);
    inline explicit STPoint3(const STVector3& v);

    inline STPoint3& operator+=(const STVector3& right);
    inline STPoint3& operator-=(const STVector3& right);

    /**
    * Returns distance between two points
    * Called as STPoint3::Dist(left, right)
    */
    static inline float Dist(const STPoint3& left, const STPoint3& right);

    /**
    * Returns distance squared between two points
    * Called as STPoint3::DistSq(left, right)
    */
    static inline float DistSq(const STPoint3& left, const STPoint3& right);

    float x, y, z;

    static const STPoint3 Origin;

    static STPoint3 Max(const STPoint3& p1, const STPoint3& p2);
    static STPoint3 Min(const STPoint3& p1, const STPoint3& p2);
};

inline STPoint3 operator+(const STPoint3& left, const STVector3& right);
inline STPoint3 operator+(const STVector3& left, const STPoint3& right);
inline STPoint3 operator-(const STPoint3& left, const STVector3& right);

inline STPoint3 operator+(const STPoint3& left, const STPoint3& right);
inline STPoint3 operator*(const STPoint3& left, const float& right);
inline STPoint3 operator/(const STPoint3& left, const float& right);

inline std::ostream& operator <<(std::ostream& stream, const STPoint3& pt);

#include "STPoint3.inl"

#endif  // __STPOINT3_H__
