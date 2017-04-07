// SSTVector4.h
#ifndef __STVector4_H__
#define __STVector4_H__

#include"STVector3.h"

//------------------------------------------------------------------------------------
// TO DO: Proj3_scenemanip
// New class
// No implementation required
//-----------------------------------------------------------------------------------

struct STVector4
{

public:
	float x, y, z, w;

public:


	// Member Function
	inline void Normalize();
	inline float DotCoord(const STVector3 & vector);
	inline float DotNormal(const STVector3 & vector);
	inline void Init(const STVector3 & p_point1, const STVector3 & p_normal);
	inline bool IsFrontFacingTo(const STVector3& direction) const;
	inline float SignedDistanceTo(const STVector3& point) const;
	inline bool RayInter( STVector3 & interPoint, const STVector3 & position, const STVector3 & direction);

	// casting
	operator float* () { return (float *) &x; }
	operator const float* () const;

	// assignment operators
	STVector4& operator += ( const STVector4& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		w += v.w;
		return (*this);
	}
	STVector4& operator -= ( const STVector4& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		w -= v.w;
		return (*this);
	}
	STVector4& operator = ( const STVector3& );
	STVector4& operator *= ( float );
	STVector4& operator /= ( float );

	// unary operators
	STVector4 operator + () const;
	STVector4 operator - () const;

	// binary operators
	/*
	STVector4 operator + ( const STVector4& ) const;
	STVector4 operator - ( const STVector4& ) const;
	*/
	STVector4 operator * ( float ) const;
	/*

	STVector4 operator / ( float ) const;
	*/
	// Comparaison operators
	bool operator == ( const STVector4& vt) const
	{
		return (( x==vt.x)&&(y==vt.y)&&(z==vt.z)&&(w==vt.w));
	}
	bool operator != ( const STVector4& ) const;

	// Member Functions
	float Length( ) const;
	float LengthSq( ) const;
	float Dot( const STVector4 &v) const;
	float Dot( const STVector3 &v) const;

	void Cross(const STVector4 &v);
	void Cross(const STVector4 &v1, const STVector4 &v2);

	void Add(const STVector4 &v);
	void Add(const STVector4 &v1, const STVector4 &v2);

	void Subtract(const STVector4 &v);
	void Subtract(const STVector4 &v1, const STVector4 &v2);

	void Minimize(const STVector4 &v);
	void Minimize(const STVector4 &v1, const STVector4 &v2);

	void Maximize(const STVector4 &v);
	void Maximize(const STVector4 &v1, const STVector4 &v2);

	void Scale(const float s);
	void Lerp(const STVector4 &v1, const STVector4 &v2, float s );

	void Cross(STVector4 &v1, const STVector4 &v2, const STVector4 &v3);

	//      void Normalize();
	void Normalize(const STVector4 &v);

	void BaryCentric(const STVector4 &v1, const STVector4 &v2, const STVector4 &v3, float f, float g);
	void Transform(const STMatrix4 &matrix );
	void Transform(const STVector4 &v, const STMatrix4 &matrix );

	/**
	merge and get smallest volume for the STVector4 sphere and another as parameter
	*/
	//void MergeBSphere(const STVector4& sph);
	/**
	is a sphere fit totaly inside another
	*/
	//bool CanFitIn(const STVector4 & wsph) const;

	static const STVector4 zero;
	static const STVector4 one;
	static const STVector4 XAxis;
	static const STVector4 YAxis;
	static const STVector4 ZAxis;
	static const STVector4 WAxis;
	static const STVector4 opXAxis;
	static const STVector4 opYAxis;
	static const STVector4 opZAxis;
	static const STVector4 opWAxis;
};

inline STVector4 vector4(float v)
{
	STVector4 ret;
	ret.x=ret.y=ret.z=ret.w=v;
	return ret;
}
inline STVector4 vector4( const STVector3& pf)
{
	STVector4 ret;
	ret.x = pf.x;
	ret.y = pf.y;
	ret.z = pf.z;
	ret.w = 0;
	return ret;
}

inline STVector4 vector4( const float* pf)
{
	STVector4 ret;
	ret.x = pf[0];
	ret.y = pf[1];
	ret.z = pf[2];
	ret.w = pf[3];
	return ret;
}
inline STVector4 vector4( float _x, float _y, float _z, float _w )
{
	STVector4 ret;
	ret.x=_x;
	ret.y=_y;
	ret.z=_z;
	ret.w=_w;
	return ret;
}
inline STVector4 vector4( float _x, float _y, float _z)
{
	STVector4 ret;
	ret.x = _x;
	ret.y = _y;
	ret.z = _z;
	ret.w = 0;
	return ret;
}


inline STVector4 vector4(const STVector3 &normal, float distance)
{
	STVector4 ret;
	ret.x = normal.x;
	ret.y = normal.y;
	ret.z = normal.z;
	ret.w = distance;
	return ret;
}

//inline STVector4 vector4(const STVector3 & point1, const STVector3 & point2, const STVector3 & point3)
//{
//	STVector4 ret;
//	STVector3 normal;
//	normal.Normal(point1, point2, point3);
//	normal.Normalize();
//	ret.w = normal.Dot(normal, point1);
//	ret.x = normal.x;
//	ret.y = normal.y;
//	ret.z = normal.z;
//	return ret;
//}

inline STVector4 vector4(const STVector4 & pt)
{
	STVector4 ret;
	ret.x = pt.x; ret.y = pt.y; ret.z = pt.z; ret.w = pt.w;
	return ret;
}


#include "STVector4.inl"

#endif  // __STVector4_H__
