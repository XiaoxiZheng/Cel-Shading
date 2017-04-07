#ifndef __STVECTOR4_INL__
#define __STVECTOR4_INL__

#include"STVector3.h"
#include"STMatrix4.h"

//------------------------------------------------------------------------------------
// TO DO: Proj3_scenemanip
// New class
// No implementation required
//-----------------------------------------------------------------------------------

///////////////////////////////////////////////////////////////////////////////////////////////////


inline STVector4 STVector4::operator + () const
{
	return *this;
}


inline STVector4 STVector4::operator - () const
{
	return vector4(-x, -y, -z, -w);
}



inline STVector4& STVector4::operator *= ( float f )
{
	x *= f;
	y *= f;
	z *= f;
	w *= f;
	return *this;
}



inline STVector4& STVector4::operator /= ( float f )
{
	float fInv = 1.0f / f;
	x *= fInv;
	y *= fInv;
	z *= fInv;
	w *= fInv;
	return *this;
}



inline STVector4 STVector4::operator * ( float f ) const
{
	return vector4(x * f, y * f, z * f, w * f);
}



///////////////////////////////////////////////////////////////////////////////////////////////////

inline float STVector4::Length( ) const
{
	return sqrtf( (x * x) + (y * y) + (z * z) + (w * w) );
}

///////////////////////////////////////////////////////////////////////////////////////////////////

inline float STVector4::LengthSq( ) const
{
	return (x * x) + (y * y) + (z * z) + (w * w);
}

///////////////////////////////////////////////////////////////////////////////////////////////////

inline float STVector4::Dot( const STVector4 &v) const
{
	return (x * v.x) + (y * v.y) + (z * v.z) + (w * v.w);
}

///////////////////////////////////////////////////////////////////////////////////////////////////

inline float STVector4::Dot( const STVector3 &v) const
{
	return (x * v.x) + (y * v.y) + (z * v.z) ;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

inline void STVector4::Cross(const STVector4 &v)
{
	STVector4 result;

	result.x = y * v.z - z * v.y;
	result.y = z * v.x - x * v.z;
	result.z = x * v.y - y * v.x;
	result.w = 0;

	*this = result;
	//return result;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

inline void STVector4::Cross(const STVector4 &v1, const STVector4 &v2)
{
	x = v1.y * v2.z - v1.z * v2.y;
	y = v1.z * v2.x - v1.x * v2.z;
	z = v1.x * v2.y - v1.y * v2.x;
	w = 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

inline void STVector4::Add(const STVector4 &v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	w += v.w;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

inline void STVector4::Add(const STVector4 &v1, const STVector4 &v2)
{
	x = v1.x + v2.x;
	y = v1.y + v2.y;
	z = v1.z + v2.z;
	w = v1.w + v2.w;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

inline void STVector4::Subtract(const STVector4 &v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	w -= v.w;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

inline void STVector4::Subtract(const STVector4 &v1, const STVector4 &v2)
{
	x = v1.x - v2.x;
	y = v1.y - v2.y;
	z = v1.z - v2.z;
	w = v1.w - v2.w;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

inline void STVector4::Minimize(const STVector4 &v)
{
	x = x < v.x ? x : v.x;
	y = y < v.y ? y : v.y;
	z = z < v.z ? z : v.z;
	w = w < v.w ? w : v.w;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

inline void STVector4::Minimize(const STVector4 &v1, const STVector4 &v2)
{
	x = v1.x < v2.x ? v1.x : v2.x;
	y = v1.y < v2.y ? v1.y : v2.y;
	z = v1.z < v2.z ? v1.z : v2.z;
	w = v1.w < v2.w ? v1.w : v2.w;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

inline void STVector4::Maximize(const STVector4 &v)
{
	x = x > v.x ? x : v.x;
	y = y > v.y ? y : v.y;
	z = z > v.z ? z : v.z;
	w = w > v.w ? w : v.w;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

inline void STVector4::Maximize(const STVector4 &v1, const STVector4 &v2)
{
	x = v1.x > v2.x ? v1.x : v2.x;
	y = v1.y > v2.y ? v1.y : v2.y;
	z = v1.z > v2.z ? v1.z : v2.z;
	w = v1.w > v2.w ? v1.w : v2.w;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

inline void STVector4::Scale(const float s)
{
	x *= s;
	y *= s;
	z *= s;
	w *= s;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

inline void STVector4::Lerp(const STVector4 &v1, const STVector4 &v2, float s )
{
	x = v1.x + s * (v2.x - v1.x);
	y = v1.y + s * (v2.y - v1.y);
	z = v1.z + s * (v2.z - v1.z);
	w = v1.w + s * (v2.w - v1.w);
}

///////////////////////////////////////////////////////////////////////////////////////////////////

inline void STVector4::Cross(STVector4 &v1, const STVector4 &v2, const STVector4 &v3)
{
	//STVector4 result;

	v1.x = v2.y * v3.z - v2.z * v3.y;
	v1.y = v2.z * v3.x - v2.x * v3.z;
	v1.z = v2.x * v3.y - v2.y * v3.x;
	v1.w = 0;

	//return result;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

inline void STVector4::Normalize()
{
	float lenght = sqrtf( (x * x) + (y * y) + (z * z) );

	if (lenght != 0.0f)
	{
		x /= lenght;
		y /= lenght;
		z /= lenght;
	}
	w = 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

inline void STVector4::Normalize(const STVector4 &/*v*/)
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////

inline void STVector4::BaryCentric(const STVector4 &/*v1*/, const STVector4 &/*v2*/, const STVector4 &/*v3*/, float /*f*/, float /*g*/)
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////

inline void STVector4::Transform(const STMatrix4 &matrix )
{
	STVector4 out;

	out.x = x * matrix.table[0][0] + y * matrix.table[1][0] + z * matrix.table[2][0] + w * matrix.table[3][0];
	out.y = x * matrix.table[0][1] + y * matrix.table[1][1] + z * matrix.table[2][1] + w * matrix.table[3][1];
	out.z = x * matrix.table[0][2] + y * matrix.table[1][2] + z * matrix.table[2][2] + w * matrix.table[3][2];
	out.w = x * matrix.table[0][3] + y * matrix.table[1][3] + z * matrix.table[2][3] + w * matrix.table[3][3];

	x = out.x;
	y = out.y;
	z = out.z;
	w = out.w;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

inline void STVector4::Transform(const STVector4 &v, const STMatrix4 &matrix )
{
	STVector4 out;

	out.x = v.x * matrix.table[0][0] + v.y * matrix.table[1][0] + v.z * matrix.table[2][0] + v.w * matrix.table[3][0];
	out.y = v.x * matrix.table[0][1] + v.y * matrix.table[1][1] + v.z * matrix.table[2][1] + v.w * matrix.table[3][1];
	out.z = v.x * matrix.table[0][2] + v.y * matrix.table[1][2] + v.z * matrix.table[2][2] + v.w * matrix.table[3][2];
	out.w = v.x * matrix.table[0][3] + v.y * matrix.table[1][3] + v.z * matrix.table[2][3] + v.w * matrix.table[3][3];

	x = out.x;
	y = out.y;
	z = out.z;
	w = out.w;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

inline void STVector4::Init(const STVector3 & p_point1, const STVector3 & p_normal)
{
	STVector3 normal;
	normal.Normalize(p_normal);
	x = normal.x;
	y = normal.y;
	z = normal.z;
	w = -normal.Dot(-normal, p_point1);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Return the signed distance between the point and the plane

inline float STVector4::DotCoord(const STVector3 & point)
{
	return STVector3(x,y,z).Dot(STVector3(x,y,z), point) + w;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Return the angle between the plane Normal and another normal

inline float STVector4::DotNormal(const STVector3 & pvector)
{
	return STVector3(x,y,z).Dot(STVector3(x,y,z), pvector);
}

///////////////////////////////////////////////////////////////////////////////////////////////////

inline bool STVector4::IsFrontFacingTo(const STVector3& direction) const
{
	float dot = STVector3(x,y,z).Dot(STVector3(x,y,z), direction);
	return (dot <=0);
}

///////////////////////////////////////////////////////////////////////////////////////////////////

inline float STVector4::SignedDistanceTo(const STVector3& point) const
{
	STVector3 dist;
	return (point.Dot(point, STVector3(x,y,z))) - w;
}

///////////////////////////////////////////////////////////////////////////////////////////////////


bool STVector4::RayInter( STVector3 & interPoint, const STVector3 & position, const STVector3 & direction)
{
	float den = STVector3(x,y,z).Dot(STVector3(x,y,z), direction);

	if( fabs(den) < 0.00001 )
	{
		return false;
	}

	STVector3 tmp = (STVector3(x,y,z) * w) - position;
	interPoint = position + (STVector3(x,y,z).Dot(STVector3(x,y,z), tmp) / den) * direction;

	return true;

}

inline STVector4& STVector4::operator = ( const STVector3& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	w = 0;
	return (*this);
}

///////////////////////////////////////////////////////////////////////////////////////////////////

//inline void STVector4::MergeBSphere(const STVector4& sph)
//{
//	if (w > (Distance(*this, sph)+sph.w) )
//		return; // sph is inside sphere
//	if (sph.w > (Distance(*this, sph)+w) )
//	{
//		// we are inside sph
//		*this = sph;
//		return;
//	}
//	float dist = Distance(*this, sph);
//	if (dist <0.001f)
//	{
//		w = (sph.w>w)?sph.w:w;
//		return;
//	}
//
//	STVector3 dir = STVector3(*this)-STVector3(sph);
//	dir /= dist;
//	STVector3 pt1 = STVector3(*this) + dir*w;
//	STVector3 pt2 = STVector3(sph) - dir*sph.w;
//	STVector3 pos = (pt1+pt2)*0.5f;
//	float r = (pt2-pt1).Length()*0.5f;
//	x = pos.x;
//	y = pos.y;
//	z = pos.z;
//	w =r;
//
//}

///////////////////////////////////////////////////////////////////////////////////////////////////

//inline bool STVector4::CanFitIn(const STVector4 & wsph) const
//{
//	if (w> wsph.w) return false;
//
//	float dist = SquaredDistance(*this, wsph);
//
//	return ((dist + w*w)<=(wsph.w*wsph.w));
//}

///////////////////////////////////////////////////////////////////////////////////////////////////

inline STVector4 vector4(const STVector3 & p_point1, const STVector3 & p_normal)
{
	STVector4 ret;
	STVector3 normal;
	normal.Normalize(p_normal);
	ret.w = normal.Dot(normal, p_point1);
	ret.x = normal.x;
	ret.y = normal.y;
	ret.z = normal.z;
	return ret;
}

#endif  // __STVECTOR4_INL__


