#pragma once

using namespace std;
using namespace DirectX;

typedef UINT uint;
typedef UINT64 uint64;
typedef unsigned char uint8;

#define Align(value, alignment) (((value + alignment - 1) / alignment) * alignment)

inline XMVECTOR Float3ToVector4(XMFLOAT3& floatVec, float w)
{
	return XMVectorSet(floatVec.x, floatVec.y, floatVec.z, w);
}

inline XMVECTOR Float3ToVector4(XMFLOAT3& floatVec)
{
	return XMVectorSet(floatVec.x, floatVec.y, floatVec.z, 1.0f);
}

inline XMFLOAT3 Vector4ToFloat3(XMVECTOR& floatVec)
{
	return XMFLOAT3(floatVec.m128_f32[0], floatVec.m128_f32[1], floatVec.m128_f32[2]);
}

inline XMFLOAT4 ToFloat4(XMFLOAT3& a, float b = 0)
{
	return XMFLOAT4(a.x, a.y, a.z, b);
}

inline XMFLOAT4 ToFloat4(XMVECTOR& a)
{
	return XMFLOAT4(a.m128_f32[0], a.m128_f32[1], a.m128_f32[2], a.m128_f32[3]);
}

inline XMFLOAT3 XMFloat3Min(const XMFLOAT3 &a, const XMFLOAT3 &b)
{
	return XMFLOAT3(
		min(a.x, b.x),
		min(a.y, b.y),
		min(a.z, b.z));
}

inline XMFLOAT3 XMFloat3Max(const XMFLOAT3 &a, const XMFLOAT3 &b)
{
	return XMFLOAT3(
		max(a.x, b.x),
		max(a.y, b.y),
		max(a.z, b.z));
}

inline XMFLOAT3 XMFloat3Add(const XMFLOAT3 &a, const XMFLOAT3 &b)
{
	return XMFLOAT3(
		a.x + b.x,
		a.y + b.y,
		a.z + b.z );
}

inline XMFLOAT3 XMFloat3Sub(const XMFLOAT3 &a, const XMFLOAT3 &b)
{
	return XMFLOAT3(
		a.x - b.x,
		a.y - b.y,
		a.z - b.z);
}

inline XMFLOAT3 XMFloat3CMul(const XMFLOAT3 &a, const float b)
{
	return XMFLOAT3(
		a.x * b,
		a.y * b,
		a.z * b);
}

inline float XMFloat3MaxElement(const XMFLOAT3 &a)
{
	return max(a.x, max(a.y, a.z));
}


struct AABB
{
	XMFLOAT3	MinBounds;
	XMFLOAT3	MaxBounds;

	AABB()
	{
		MinBounds = XMFLOAT3(FLT_MAX, FLT_MAX, FLT_MAX);
		MaxBounds = XMFLOAT3(-FLT_MAX, -FLT_MAX, -FLT_MAX);
	}

	void Expand(XMFLOAT3& point)
	{
		MinBounds = XMFloat3Min(MinBounds, point);
		MaxBounds = XMFloat3Max(MaxBounds, point);
	}

	void Expand(AABB& aabox)
	{
		Expand(aabox.MinBounds);
		Expand(aabox.MaxBounds);
	}

	XMFLOAT3 GetCentre()
	{
		return  XMFloat3CMul( XMFloat3Add(MaxBounds, MinBounds), 0.5f );
	}

};
 
