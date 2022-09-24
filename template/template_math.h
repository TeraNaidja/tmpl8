#pragma once

// aligned memory allocations
#ifdef _MSC_VER
#define ALIGN( x ) __declspec( align( x ) )
#define MALLOC64( x ) ( ( x ) == 0 ? 0 : _aligned_malloc( ( x ), 64 ) )
#define FREE64( x ) _aligned_free( x )
#else
#define ALIGN( x ) __attribute__( ( aligned( x ) ) )
#define MALLOC64( x ) ( ( x ) == 0 ? 0 : aligned_alloc( 64, ( x ) ) )
#define FREE64( x ) free( x )
#endif

namespace Tmpl8
{
	// vector type placeholders, carefully matching OpenCL's layout and alignment
	struct ALIGN(8) int2
	{
		int2() = default;
		int2(const int a, const int b) : x(a), y(b) {}
		int2(const int a) : x(a), y(a) {}
		union { struct { int x, y; }; int cell[2]; };
		int& operator [] (const int n) { return cell[n]; }
	};
	struct ALIGN(8) uint2
	{
		uint2() = default;
		uint2(const int a, const int b) : x(a), y(b) {}
		uint2(const uint a) : x(a), y(a) {}
		union { struct { uint x, y; }; uint cell[2]; };
		uint& operator [] (const int n) { return cell[n]; }
	};
	struct ALIGN(8) float2
	{
		float2() = default;
		float2(const float a, const float b) : x(a), y(b) {}
		float2(const float a) : x(a), y(a) {}
		union { struct { float x, y; }; float cell[2]; };
		float& operator [] (const int n) { return cell[n]; }
	};
	struct int3;
	struct ALIGN(16) int4
	{
		int4() = default;
		int4(const int a, const int b, const int c, const int d) : x(a), y(b), z(c), w(d) {}
		int4(const int a) : x(a), y(a), z(a), w(a) {}
		int4(const int3 & a, const int d);
		union { struct { int x, y, z, w; }; int cell[4]; };
		int& operator [] (const int n) { return cell[n]; }
	};
	struct ALIGN(16) int3
	{
		int3() = default;
		int3(const int a, const int b, const int c) : x(a), y(b), z(c) {}
		int3(const int a) : x(a), y(a), z(a) {}
		int3(const int4 a) : x(a.x), y(a.y), z(a.z) {}
		union { struct { int x, y, z; int dummy; }; int cell[4]; };
		int& operator [] (const int n) { return cell[n]; }
	};
	struct uint3;
	struct ALIGN(16) uint4
	{
		uint4() = default;
		uint4(const uint a, const uint b, const uint c, const uint d) : x(a), y(b), z(c), w(d) {}
		uint4(const uint a) : x(a), y(a), z(a), w(a) {}
		uint4(const uint3 & a, const uint d);
		union { struct { uint x, y, z, w; }; uint cell[4]; };
		uint& operator [] (const int n) { return cell[n]; }
	};
	struct ALIGN(16) uint3
	{
		uint3() = default;
		uint3(const uint a, const uint b, const uint c) : x(a), y(b), z(c) {}
		uint3(const uint a) : x(a), y(a), z(a) {}
		uint3(const uint4 a) : x(a.x), y(a.y), z(a.z) {}
		union { struct { uint x, y, z; uint dummy; }; uint cell[4]; };
		uint& operator [] (const int n) { return cell[n]; }
	};
	struct float3;
	struct ALIGN(16) float4
	{
		float4() = default;
		float4(const float a, const float b, const float c, const float d) : x(a), y(b), z(c), w(d) {}
		float4(const float a) : x(a), y(a), z(a), w(a) {}
		float4(const float3 & a, const float d);
		float4(const float3 & a);
		union { struct { float x, y, z, w; }; float cell[4]; };
		float& operator [] (const int n) { return cell[n]; }
	};
	struct float3
	{
		float3() = default;
		float3(const float a, const float b, const float c) : x(a), y(b), z(c) {}
		float3(const float a) : x(a), y(a), z(a) {}
		float3(const float4 a) : x(a.x), y(a.y), z(a.z) {}
		float3(const uint3 a) : x((float)a.x), y((float)a.y), z((float)a.z) {}
		union { struct { float x, y, z; }; float cell[3]; };
		float& operator [] (const int n) { return cell[n]; }
	};
	struct ALIGN(4) uchar4
	{
		uchar4() = default;
		uchar4(const uchar a, const uchar b, const uchar c, const uchar d) : x(a), y(b), z(c), w(d) {}
		uchar4(const uchar a) : x(a), y(a), z(a), w(a) {}
		union { struct { uchar x, y, z, w; }; uchar cell[4]; };
		uchar& operator [] (const int n) { return cell[n]; }
	};

	inline float2 make_float2(const float a, float b) { float2 f2; f2.x = a, f2.y = b; return f2; }
	inline float2 make_float2(const float s) { return make_float2(s, s); }
	inline float2 make_float2(const float3& a) { return make_float2(a.x, a.y); }
	inline float2 make_float2(const int2& a) { return make_float2(float(a.x), float(a.y)); } // explicit casts prevent gcc warnings
	inline float2 make_float2(const uint2& a) { return make_float2(float(a.x), float(a.y)); }
	inline int2 make_int2(const int a, const int b) { int2 i2; i2.x = a, i2.y = b; return i2; }
	inline int2 make_int2(const int s) { return make_int2(s, s); }
	inline int2 make_int2(const int3& a) { return make_int2(a.x, a.y); }
	inline int2 make_int2(const uint2& a) { return make_int2(int(a.x), int(a.y)); }
	inline int2 make_int2(const float2& a) { return make_int2(int(a.x), int(a.y)); }
	inline uint2 make_uint2(const uint a, const uint b) { uint2 u2; u2.x = a, u2.y = b; return u2; }
	inline uint2 make_uint2(const uint s) { return make_uint2(s, s); }
	inline uint2 make_uint2(const uint3& a) { return make_uint2(a.x, a.y); }
	inline uint2 make_uint2(const int2& a) { return make_uint2(uint(a.x), uint(a.y)); }
	inline float3 make_float3(const float& a, const float& b, const float& c) { float3 f3; f3.x = a, f3.y = b, f3.z = c; return f3; }
	inline float3 make_float3(const float& s) { return make_float3(s, s, s); }
	inline float3 make_float3(const float2& a) { return make_float3(a.x, a.y, 0.0f); }
	inline float3 make_float3(const float2& a, const float& s) { return make_float3(a.x, a.y, s); }
	inline float3 make_float3(const float4& a) { return make_float3(a.x, a.y, a.z); }
	inline float3 make_float3(const int3& a) { return make_float3(float(a.x), float(a.y), float(a.z)); }
	inline float3 make_float3(const uint3& a) { return make_float3(float(a.x), float(a.y), float(a.z)); }
	inline int3 make_int3(const int& a, const int& b, const int& c) { int3 i3; i3.x = a, i3.y = b, i3.z = c; return i3; }
	inline int3 make_int3(const int& s) { return make_int3(s, s, s); }
	inline int3 make_int3(const int2& a) { return make_int3(a.x, a.y, 0); }
	inline int3 make_int3(const int2& a, const int& s) { return make_int3(a.x, a.y, s); }
	inline int3 make_int3(const uint3& a) { return make_int3(int(a.x), int(a.y), int(a.z)); }
	inline int3 make_int3(const float3& a) { return make_int3(int(a.x), int(a.y), int(a.z)); }
	inline int3 make_int3(const float4& a) { return make_int3(int(a.x), int(a.y), int(a.z)); }
	inline uint3 make_uint3(const uint a, uint b, uint c) { uint3 u3; u3.x = a, u3.y = b, u3.z = c; return u3; }
	inline uint3 make_uint3(const uint s) { return make_uint3(s, s, s); }
	inline uint3 make_uint3(const uint2& a) { return make_uint3(a.x, a.y, 0); }
	inline uint3 make_uint3(const uint2& a, const uint s) { return make_uint3(a.x, a.y, s); }
	inline uint3 make_uint3(const uint4& a) { return make_uint3(a.x, a.y, a.z); }
	inline uint3 make_uint3(const int3& a) { return make_uint3(uint(a.x), uint(a.y), uint(a.z)); }
	inline float4 make_float4(const float a, const float b, const float c, const float d) { float4 f4; f4.x = a, f4.y = b, f4.z = c, f4.w = d; return f4; }
	inline float4 make_float4(const float s) { return make_float4(s, s, s, s); }
	inline float4 make_float4(const float3& a) { return make_float4(a.x, a.y, a.z, 0.0f); }
	inline float4 make_float4(const float3& a, const float w) { return make_float4(a.x, a.y, a.z, w); }
	inline float4 make_float4(const int3& a, const float w) { return make_float4((float)a.x, (float)a.y, (float)a.z, w); }
	inline float4 make_float4(const int4& a) { return make_float4(float(a.x), float(a.y), float(a.z), float(a.w)); }
	inline float4 make_float4(const uint4& a) { return make_float4(float(a.x), float(a.y), float(a.z), float(a.w)); }
	inline int4 make_int4(const int a, const int b, const int c, const int d) { int4 i4; i4.x = a, i4.y = b, i4.z = c, i4.w = d; return i4; }
	inline int4 make_int4(const int s) { return make_int4(s, s, s, s); }
	inline int4 make_int4(const int3& a) { return make_int4(a.x, a.y, a.z, 0); }
	inline int4 make_int4(const int3& a, const int w) { return make_int4(a.x, a.y, a.z, w); }
	inline int4 make_int4(const uint4& a) { return make_int4(int(a.x), int(a.y), int(a.z), int(a.w)); }
	inline int4 make_int4(const float4& a) { return make_int4(int(a.x), int(a.y), int(a.z), int(a.w)); }
	inline uint4 make_uint4(const uint a, const uint b, const uint c, const uint d) { uint4 u4; u4.x = a, u4.y = b, u4.z = c, u4.w = d; return u4; }
	inline uint4 make_uint4(const uint s) { return make_uint4(s, s, s, s); }
	inline uint4 make_uint4(const uint3& a) { return make_uint4(a.x, a.y, a.z, 0); }
	inline uint4 make_uint4(const uint3& a, const uint w) { return make_uint4(a.x, a.y, a.z, w); }
	inline uint4 make_uint4(const int4& a) { return make_uint4(uint(a.x), uint(a.y), uint(a.z), uint(a.w)); }
	inline uchar4 make_uchar4(const uchar a, const uchar b, const uchar c, const uchar d) { uchar4 c4; c4.x = a, c4.y = b, c4.z = c, c4.w = d; return c4; }

	inline float2 operator-(const float2& a) { return make_float2(-a.x, -a.y); }
	inline int2 operator-(const int2& a) { return make_int2(-a.x, -a.y); }
	inline float3 operator-(const float3& a) { return make_float3(-a.x, -a.y, -a.z); }
	inline int3 operator-(const int3& a) { return make_int3(-a.x, -a.y, -a.z); }
	inline float4 operator-(const float4& a) { return make_float4(-a.x, -a.y, -a.z, -a.w); }
	inline int4 operator-(const int4& a) { return make_int4(-a.x, -a.y, -a.z, -a.w); }
	inline int2 operator << (const int2& a, int b) { return make_int2(a.x << b, a.y << b); }
	inline int2 operator >> (const int2& a, int b) { return make_int2(a.x >> b, a.y >> b); }
	inline int3 operator << (const int3& a, int b) { return make_int3(a.x << b, a.y << b, a.z << b); }
	inline int3 operator >> (const int3& a, int b) { return make_int3(a.x >> b, a.y >> b, a.z >> b); }
	inline int4 operator << (const int4& a, int b) { return make_int4(a.x << b, a.y << b, a.z << b, a.w << b); }
	inline int4 operator >> (const int4& a, int b) { return make_int4(a.x >> b, a.y >> b, a.z >> b, a.w >> b); }

	inline float2 operator+(const float2& a, const float2& b) { return make_float2(a.x + b.x, a.y + b.y); }
	inline float2 operator+(const float2& a, const int2& b) { return make_float2(a.x + (float)b.x, a.y + (float)b.y); }
	inline float2 operator+(const float2& a, const uint2& b) { return make_float2(a.x + (float)b.x, a.y + (float)b.y); }
	inline float2 operator+(const int2& a, const float2& b) { return make_float2((float)a.x + b.x, (float)a.y + b.y); }
	inline float2 operator+(const uint2& a, const float2& b) { return make_float2((float)a.x + b.x, (float)a.y + b.y); }
	inline void operator+=(float2& a, const float2& b) { a.x += b.x;	a.y += b.y; }
	inline void operator+=(float2& a, const int2& b) { a.x += (float)b.x; a.y += (float)b.y; }
	inline void operator+=(float2& a, const uint2& b) { a.x += (float)b.x; a.y += (float)b.y; }
	inline float2 operator+(const float2& a, float b) { return make_float2(a.x + b, a.y + b); }
	inline float2 operator+(const float2& a, int b) { return make_float2(a.x + (float)b, a.y + (float)b); }
	inline float2 operator+(const float2& a, uint b) { return make_float2(a.x + (float)b, a.y + (float)b); }
	inline float2 operator+(float b, const float2& a) { return make_float2(a.x + b, a.y + b); }
	inline void operator+=(float2& a, float b) { a.x += b; a.y += b; }
	inline void operator+=(float2& a, int b) { a.x += (float)b; a.y += (float)b; }
	inline void operator+=(float2& a, uint b) { a.x += (float)b;	a.y += (float)b; }
	inline int2 operator+(const int2& a, const int2& b) { return make_int2(a.x + b.x, a.y + b.y); }
	inline void operator+=(int2& a, const int2& b) { a.x += b.x;	a.y += b.y; }
	inline int2 operator+(const int2& a, int b) { return make_int2(a.x + b, a.y + b); }
	inline int2 operator+(int b, const int2& a) { return make_int2(a.x + b, a.y + b); }
	inline void operator+=(int2& a, int b) { a.x += b;	a.y += b; }
	inline uint2 operator+(const uint2& a, const uint2& b) { return make_uint2(a.x + b.x, a.y + b.y); }
	inline void operator+=(uint2& a, const uint2& b) { a.x += b.x;	a.y += b.y; }
	inline uint2 operator+(const uint2& a, uint b) { return make_uint2(a.x + b, a.y + b); }
	inline uint2 operator+(uint b, const uint2& a) { return make_uint2(a.x + b, a.y + b); }
	inline void operator+=(uint2& a, uint b) { a.x += b;	a.y += b; }
	inline float3 operator+(const float3& a, const float3& b) { return make_float3(a.x + b.x, a.y + b.y, a.z + b.z); }
	inline float3 operator+(const float3& a, const int3& b) { return make_float3(a.x + (float)b.x, a.y + (float)b.y, a.z + (float)b.z); }
	inline float3 operator+(const float3& a, const uint3& b) { return make_float3(a.x + (float)b.x, a.y + (float)b.y, a.z + (float)b.z); }
	inline float3 operator+(const int3& a, const float3& b) { return make_float3((float)a.x + b.x, (float)a.y + b.y, (float)a.z + b.z); }
	inline float3 operator+(const uint3& a, const float3& b) { return make_float3((float)a.x + b.x, (float)a.y + b.y, (float)a.z + b.z); }
	inline void operator+=(float3& a, const float3& b) { a.x += b.x;	a.y += b.y;	a.z += b.z; }
	inline void operator+=(float3& a, const int3& b) { a.x += (float)b.x; a.y += (float)b.y; a.z += (float)b.z; }
	inline void operator+=(float3& a, const uint3& b) { a.x += (float)b.x; a.y += (float)b.y; a.z += (float)b.z; }
	inline float3 operator+(const float3& a, float b) { return make_float3(a.x + b, a.y + b, a.z + b); }
	inline float3 operator+(const float3& a, int b) { return make_float3(a.x + (float)b, a.y + (float)b, a.z + (float)b); }
	inline float3 operator+(const float3& a, uint b) { return make_float3(a.x + (float)b, a.y + (float)b, a.z + (float)b); }
	inline void operator+=(float3& a, float b) { a.x += b; a.y += b;	a.z += b; }
	inline void operator+=(float3& a, int b) { a.x += (float)b; a.y += (float)b; a.z += (float)b; }
	inline void operator+=(float3& a, uint b) { a.x += (float)b; a.y += (float)b; a.z += (float)b; }
	inline int3 operator+(const int3& a, const int3& b) { return make_int3(a.x + b.x, a.y + b.y, a.z + b.z); }
	inline void operator+=(int3& a, const int3& b) { a.x += b.x;	a.y += b.y;	a.z += b.z; }
	inline int3 operator+(const int3& a, int b) { return make_int3(a.x + b, a.y + b, a.z + b); }
	inline void operator+=(int3& a, int b) { a.x += b;	a.y += b;	a.z += b; }
	inline uint3 operator+(const uint3& a, const uint3& b) { return make_uint3(a.x + b.x, a.y + b.y, a.z + b.z); }
	inline void operator+=(uint3& a, const uint3& b) { a.x += b.x;	a.y += b.y;	a.z += b.z; }
	inline uint3 operator+(const uint3& a, uint b) { return make_uint3(a.x + b, a.y + b, a.z + b); }
	inline void operator+=(uint3& a, uint b) { a.x += b;	a.y += b;	a.z += b; }
	inline int3 operator+(int b, const int3& a) { return make_int3(a.x + b, a.y + b, a.z + b); }
	inline uint3 operator+(uint b, const uint3& a) { return make_uint3(a.x + b, a.y + b, a.z + b); }
	inline float3 operator+(float b, const float3& a) { return make_float3(a.x + b, a.y + b, a.z + b); }
	inline float4 operator+(const float4& a, const float4& b) { return make_float4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w); }
	inline float4 operator+(const float4& a, const int4& b) { return make_float4(a.x + (float)b.x, a.y + (float)b.y, a.z + (float)b.z, a.w + (float)b.w); }
	inline float4 operator+(const float4& a, const uint4& b) { return make_float4(a.x + (float)b.x, a.y + (float)b.y, a.z + (float)b.z, a.w + (float)b.w); }
	inline float4 operator+(const int4& a, const float4& b) { return make_float4((float)a.x + b.x, (float)a.y + b.y, (float)a.z + b.z, (float)a.w + b.w); }
	inline float4 operator+(const uint4& a, const float4& b) { return make_float4((float)a.x + b.x, (float)a.y + b.y, (float)a.z + b.z, (float)a.w + b.w); }
	inline void operator+=(float4& a, const float4& b) { a.x += b.x;	a.y += b.y;	a.z += b.z;	a.w += b.w; }
	inline void operator+=(float4& a, const int4& b) { a.x += (float)b.x; a.y += (float)b.y; a.z += (float)b.z; a.w += (float)b.w; }
	inline void operator+=(float4& a, const uint4& b) { a.x += (float)b.x; a.y += (float)b.y; a.z += (float)b.z; a.w += (float)b.w; }
	inline float4 operator+(const float4& a, float b) { return make_float4(a.x + b, a.y + b, a.z + b, a.w + b); }
	inline float4 operator+(const float4& a, int b) { return make_float4(a.x + (float)b, a.y + (float)b, a.z + (float)b, a.w + (float)b); }
	inline float4 operator+(const float4& a, uint b) { return make_float4(a.x + (float)b, a.y + (float)b, a.z + (float)b, a.w + (float)b); }
	inline float4 operator+(float b, const float4& a) { return make_float4(a.x + b, a.y + b, a.z + b, a.w + b); }
	inline void operator+=(float4& a, float b) { a.x += b;	a.y += b;	a.z += b;	a.w += b; }
	inline void operator+=(float4& a, int b) { a.x += (float)b; a.y += (float)b; a.z += (float)b; a.w += (float)b; }
	inline void operator+=(float4& a, uint b) { a.x += (float)b; a.y += (float)b; a.z += (float)b; a.w += (float)b; }
	inline int4 operator+(const int4& a, const int4& b) { return make_int4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w); }
	inline void operator+=(int4& a, const int4& b) { a.x += b.x;	a.y += b.y;	a.z += b.z;	a.w += b.w; }
	inline int4 operator+(const int4& a, int b) { return make_int4(a.x + b, a.y + b, a.z + b, a.w + b); }
	inline int4 operator+(int b, const int4& a) { return make_int4(a.x + b, a.y + b, a.z + b, a.w + b); }
	inline void operator+=(int4& a, int b) { a.x += b;	a.y += b;	a.z += b;	a.w += b; }
	inline uint4 operator+(const uint4& a, const uint4& b) { return make_uint4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w); }
	inline void operator+=(uint4& a, const uint4& b) { a.x += b.x;	a.y += b.y;	a.z += b.z;	a.w += b.w; }
	inline uint4 operator+(const uint4& a, uint b) { return make_uint4(a.x + b, a.y + b, a.z + b, a.w + b); }
	inline uint4 operator+(uint b, const uint4& a) { return make_uint4(a.x + b, a.y + b, a.z + b, a.w + b); }
	inline void operator+=(uint4& a, uint b) { a.x += b;	a.y += b;	a.z += b;	a.w += b; }

	inline float2 operator-(const float2& a, const float2& b) { return make_float2(a.x - b.x, a.y - b.y); }
	inline float2 operator-(const float2& a, const int2& b) { return make_float2(a.x - (float)b.x, a.y - (float)b.y); }
	inline float2 operator-(const float2& a, const uint2& b) { return make_float2(a.x - (float)b.x, a.y - (float)b.y); }
	inline float2 operator-(const int2& a, const float2& b) { return make_float2((float)a.x - b.x, (float)a.y - b.y); }
	inline float2 operator-(const uint2& a, const float2& b) { return make_float2((float)a.x - b.x, (float)a.y - b.y); }
	inline void operator-=(float2& a, const float2& b) { a.x -= b.x;	a.y -= b.y; }
	inline void operator-=(float2& a, const int2& b) { a.x -= (float)b.x; a.y -= (float)b.y; }
	inline void operator-=(float2& a, const uint2& b) { a.x -= (float)b.x; a.y -= (float)b.y; }
	inline float2 operator-(const float2& a, float b) { return make_float2(a.x - b, a.y - b); }
	inline float2 operator-(const float2& a, int b) { return make_float2(a.x - (float)b, a.y - (float)b); }
	inline float2 operator-(const float2& a, uint b) { return make_float2(a.x - (float)b, a.y - (float)b); }
	inline float2 operator-(float b, const float2& a) { return make_float2(b - a.x, b - a.y); }
	inline void operator-=(float2& a, float b) { a.x -= b; a.y -= b; }
	inline void operator-=(float2& a, int b) { a.x -= (float)b; a.y -= (float)b; }
	inline void operator-=(float2& a, uint b) { a.x -= (float)b; a.y -= (float)b; }
	inline int2 operator-(const int2& a, const int2& b) { return make_int2(a.x - b.x, a.y - b.y); }
	inline void operator-=(int2& a, const int2& b) { a.x -= b.x;	a.y -= b.y; }
	inline int2 operator-(const int2& a, int b) { return make_int2(a.x - b, a.y - b); }
	inline int2 operator-(int b, const int2& a) { return make_int2(b - a.x, b - a.y); }
	inline void operator-=(int2& a, int b) { a.x -= b;	a.y -= b; }
	inline uint2 operator-(const uint2& a, const uint2& b) { return make_uint2(a.x - b.x, a.y - b.y); }
	inline void operator-=(uint2& a, const uint2& b) { a.x -= b.x;	a.y -= b.y; }
	inline uint2 operator-(const uint2& a, uint b) { return make_uint2(a.x - b, a.y - b); }
	inline uint2 operator-(uint b, const uint2& a) { return make_uint2(b - a.x, b - a.y); }
	inline void operator-=(uint2& a, uint b) { a.x -= b;	a.y -= b; }
	inline float3 operator-(const float3& a, const float3& b) { return make_float3(a.x - b.x, a.y - b.y, a.z - b.z); }
	inline float3 operator-(const float3& a, const int3& b) { return make_float3(a.x - (float)b.x, a.y - (float)b.y, a.z - (float)b.z); }
	inline float3 operator-(const float3& a, const uint3& b) { return make_float3(a.x - (float)b.x, a.y - (float)b.y, a.z - (float)b.z); }
	inline float3 operator-(const int3& a, const float3& b) { return make_float3((float)a.x - b.x, (float)a.y - b.y, (float)a.z - b.z); }
	inline float3 operator-(const uint3& a, const float3& b) { return make_float3((float)a.x - b.x, (float)a.y - b.y, (float)a.z - b.z); }
	inline void operator-=(float3& a, const float3& b) { a.x -= b.x;	a.y -= b.y;	a.z -= b.z; }
	inline void operator-=(float3& a, const int3& b) { a.x -= (float)b.x; a.y -= (float)b.y; a.z -= (float)b.z; }
	inline void operator-=(float3& a, const uint3& b) { a.x -= (float)b.x; a.y -= (float)b.y; a.z -= (float)b.z; }
	inline float3 operator-(const float3& a, float b) { return make_float3(a.x - b, a.y - b, a.z - b); }
	inline float3 operator-(const float3& a, int b) { return make_float3(a.x - (float)b, a.y - (float)b, a.z - (float)b); }
	inline float3 operator-(const float3& a, uint b) { return make_float3(a.x - (float)b, a.y - (float)b, a.z - (float)b); }
	inline float3 operator-(float b, const float3& a) { return make_float3(b - a.x, b - a.y, b - a.z); }
	inline void operator-=(float3& a, float b) { a.x -= b; a.y -= b; a.z -= b; }
	inline void operator-=(float3& a, int b) { a.x -= (float)b; a.y -= (float)b; a.z -= (float)b; }
	inline void operator-=(float3& a, uint b) { a.x -= (float)b;	a.y -= (float)b; a.z -= (float)b; }
	inline int3 operator-(const int3& a, const int3& b) { return make_int3(a.x - b.x, a.y - b.y, a.z - b.z); }
	inline void operator-=(int3& a, const int3& b) { a.x -= b.x;	a.y -= b.y;	a.z -= b.z; }
	inline int3 operator-(const int3& a, int b) { return make_int3(a.x - b, a.y - b, a.z - b); }
	inline int3 operator-(int b, const int3& a) { return make_int3(b - a.x, b - a.y, b - a.z); }
	inline void operator-=(int3& a, int b) { a.x -= b;	a.y -= b;	a.z -= b; }
	inline uint3 operator-(const uint3& a, const uint3& b) { return make_uint3(a.x - b.x, a.y - b.y, a.z - b.z); }
	inline void operator-=(uint3& a, const uint3& b) { a.x -= b.x;	a.y -= b.y;	a.z -= b.z; }
	inline uint3 operator-(const uint3& a, uint b) { return make_uint3(a.x - b, a.y - b, a.z - b); }
	inline uint3 operator-(uint b, const uint3& a) { return make_uint3(b - a.x, b - a.y, b - a.z); }
	inline void operator-=(uint3& a, uint b) { a.x -= b;	a.y -= b;	a.z -= b; }
	inline float4 operator-(const float4& a, const float4& b) { return make_float4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w); }
	inline float4 operator-(const float4& a, const int4& b) { return make_float4(a.x - (float)b.x, a.y - (float)b.y, a.z - (float)b.z, a.w - (float)b.w); }
	inline float4 operator-(const float4& a, const uint4& b) { return make_float4(a.x - (float)b.x, a.y - (float)b.y, a.z - (float)b.z, a.w - (float)b.w); }
	inline float4 operator-(const int4& a, const float4& b) { return make_float4((float)a.x - b.x, (float)a.y - b.y, (float)a.z - b.z, (float)a.w - b.w); }
	inline float4 operator-(const uint4& a, const float4& b) { return make_float4((float)a.x - b.x, (float)a.y - b.y, (float)a.z - b.z, (float)a.w - b.w); }
	inline void operator-=(float4& a, const float4& b) { a.x -= b.x;	a.y -= b.y;	a.z -= b.z;	a.w -= b.w; }
	inline void operator-=(float4& a, const int4& b) { a.x -= (float)b.x; a.y -= (float)b.y; a.z -= (float)b.z; a.w -= (float)b.w; }
	inline void operator-=(float4& a, const uint4& b) { a.x -= (float)b.x; a.y -= (float)b.y; a.z -= (float)b.z; a.w -= (float)b.w; }
	inline float4 operator-(const float4& a, float b) { return make_float4(a.x - b, a.y - b, a.z - b, a.w - b); }
	inline float4 operator-(const float4& a, int b) { return make_float4(a.x - (float)b, a.y - (float)b, a.z - (float)b, a.w - (float)b); }
	inline float4 operator-(const float4& a, uint b) { return make_float4(a.x - (float)b, a.y - (float)b, a.z - (float)b, a.w - (float)b); }
	inline void operator-=(float4& a, float b) { a.x -= b; a.y -= b; a.z -= b; a.w -= b; }
	inline void operator-=(float4& a, int b) { a.x -= (float)b; a.y -= (float)b; a.z -= (float)b; a.w -= (float)b; }
	inline void operator-=(float4& a, uint b) { a.x -= (float)b; a.y -= (float)b; a.z -= (float)b; a.w -= (float)b; }
	inline int4 operator-(const int4& a, const int4& b) { return make_int4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w); }
	inline void operator-=(int4& a, const int4& b) { a.x -= b.x;	a.y -= b.y;	a.z -= b.z;	a.w -= b.w; }
	inline int4 operator-(const int4& a, int b) { return make_int4(a.x - b, a.y - b, a.z - b, a.w - b); }
	inline int4 operator-(int b, const int4& a) { return make_int4(b - a.x, b - a.y, b - a.z, b - a.w); }
	inline void operator-=(int4& a, int b) { a.x -= b;	a.y -= b;	a.z -= b;	a.w -= b; }
	inline uint4 operator-(const uint4& a, const uint4& b) { return make_uint4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w); }
	inline void operator-=(uint4& a, const uint4& b) { a.x -= b.x;	a.y -= b.y;	a.z -= b.z;	a.w -= b.w; }
	inline uint4 operator-(const uint4& a, uint b) { return make_uint4(a.x - b, a.y - b, a.z - b, a.w - b); }
	inline uint4 operator-(uint b, const uint4& a) { return make_uint4(b - a.x, b - a.y, b - a.z, b - a.w); }
	inline void operator-=(uint4& a, uint b) { a.x -= b;	a.y -= b;	a.z -= b;	a.w -= b; }

	inline float2 operator*(const float2& a, const float2& b) { return make_float2(a.x * b.x, a.y * b.y); }
	inline void operator*=(float2& a, const float2& b) { a.x *= b.x;	a.y *= b.y; }
	inline float2 operator*(const float2& a, float b) { return make_float2(a.x * b, a.y * b); }
	inline float2 operator*(float b, const float2& a) { return make_float2(b * a.x, b * a.y); }
	inline void operator*=(float2& a, float b) { a.x *= b;	a.y *= b; }
	inline int2 operator*(const int2& a, const int2& b) { return make_int2(a.x * b.x, a.y * b.y); }
	inline void operator*=(int2& a, const int2& b) { a.x *= b.x;	a.y *= b.y; }
	inline int2 operator*(const int2& a, int b) { return make_int2(a.x * b, a.y * b); }
	inline int2 operator*(int b, const int2& a) { return make_int2(b * a.x, b * a.y); }
	inline void operator*=(int2& a, int b) { a.x *= b;	a.y *= b; }
	inline uint2 operator*(const uint2& a, const uint2& b) { return make_uint2(a.x * b.x, a.y * b.y); }
	inline void operator*=(uint2& a, const uint2& b) { a.x *= b.x;	a.y *= b.y; }
	inline uint2 operator*(const uint2& a, uint b) { return make_uint2(a.x * b, a.y * b); }
	inline uint2 operator*(uint b, const uint2& a) { return make_uint2(b * a.x, b * a.y); }
	inline void operator*=(uint2& a, uint b) { a.x *= b;	a.y *= b; }
	inline float3 operator*(const float3& a, const float3& b) { return make_float3(a.x * b.x, a.y * b.y, a.z * b.z); }
	inline void operator*=(float3& a, const float3& b) { a.x *= b.x;	a.y *= b.y;	a.z *= b.z; }
	inline float3 operator*(const float3& a, float b) { return make_float3(a.x * b, a.y * b, a.z * b); }
	inline float3 operator*(float b, const float3& a) { return make_float3(b * a.x, b * a.y, b * a.z); }
	inline void operator*=(float3& a, float b) { a.x *= b;	a.y *= b;	a.z *= b; }
	inline int3 operator*(const int3& a, const int3& b) { return make_int3(a.x * b.x, a.y * b.y, a.z * b.z); }
	inline void operator*=(int3& a, const int3& b) { a.x *= b.x;	a.y *= b.y;	a.z *= b.z; }
	inline int3 operator*(const int3& a, int b) { return make_int3(a.x * b, a.y * b, a.z * b); }
	inline int3 operator*(int b, const int3& a) { return make_int3(b * a.x, b * a.y, b * a.z); }
	inline void operator*=(int3& a, int b) { a.x *= b;	a.y *= b;	a.z *= b; }
	inline uint3 operator*(const uint3& a, const uint3& b) { return make_uint3(a.x * b.x, a.y * b.y, a.z * b.z); }
	inline void operator*=(uint3& a, const uint3& b) { a.x *= b.x;	a.y *= b.y;	a.z *= b.z; }
	inline uint3 operator*(const uint3& a, uint b) { return make_uint3(a.x * b, a.y * b, a.z * b); }
	inline uint3 operator*(uint b, const uint3& a) { return make_uint3(b * a.x, b * a.y, b * a.z); }
	inline void operator*=(uint3& a, uint b) { a.x *= b;	a.y *= b;	a.z *= b; }
	inline float4 operator*(const float4& a, const float4& b) { return make_float4(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w); }
	inline void operator*=(float4& a, const float4& b) { a.x *= b.x;	a.y *= b.y;	a.z *= b.z;	a.w *= b.w; }
	inline float4 operator*(const float4& a, float b) { return make_float4(a.x * b, a.y * b, a.z * b, a.w * b); }
	inline float4 operator*(float b, const float4& a) { return make_float4(b * a.x, b * a.y, b * a.z, b * a.w); }
	inline void operator*=(float4& a, float b) { a.x *= b;	a.y *= b;	a.z *= b;	a.w *= b; }
	inline int4 operator*(const int4& a, const int4& b) { return make_int4(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w); }
	inline void operator*=(int4& a, const int4& b) { a.x *= b.x;	a.y *= b.y;	a.z *= b.z;	a.w *= b.w; }
	inline int4 operator*(const int4& a, int b) { return make_int4(a.x * b, a.y * b, a.z * b, a.w * b); }
	inline int4 operator*(int b, const int4& a) { return make_int4(b * a.x, b * a.y, b * a.z, b * a.w); }
	inline void operator*=(int4& a, int b) { a.x *= b;	a.y *= b;	a.z *= b;	a.w *= b; }
	inline uint4 operator*(const uint4& a, const uint4& b) { return make_uint4(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w); }
	inline void operator*=(uint4& a, const uint4& b) { a.x *= b.x;	a.y *= b.y;	a.z *= b.z;	a.w *= b.w; }
	inline uint4 operator*(const uint4& a, uint b) { return make_uint4(a.x * b, a.y * b, a.z * b, a.w * b); }
	inline uint4 operator*(uint b, const uint4& a) { return make_uint4(b * a.x, b * a.y, b * a.z, b * a.w); }
	inline void operator*=(uint4& a, uint b) { a.x *= b;	a.y *= b;	a.z *= b;	a.w *= b; }

	inline float2 operator/(const float2& a, const float2& b) { return make_float2(a.x / b.x, a.y / b.y); }
	inline void operator/=(float2& a, const float2& b) { a.x /= b.x;	a.y /= b.y; }
	inline float2 operator/(const float2& a, float b) { return make_float2(a.x / b, a.y / b); }
	inline void operator/=(float2& a, float b) { a.x /= b;	a.y /= b; }
	inline float2 operator/(float b, const float2& a) { return make_float2(b / a.x, b / a.y); }
	inline float3 operator/(const float3& a, const float3& b) { return make_float3(a.x / b.x, a.y / b.y, a.z / b.z); }
	inline void operator/=(float3& a, const float3& b) { a.x /= b.x;	a.y /= b.y;	a.z /= b.z; }
	inline float3 operator/(const float3& a, float b) { return make_float3(a.x / b, a.y / b, a.z / b); }
	inline void operator/=(float3& a, float b) { a.x /= b;	a.y /= b;	a.z /= b; }
	inline float3 operator/(float b, const float3& a) { return make_float3(b / a.x, b / a.y, b / a.z); }
	inline float4 operator/(const float4& a, const float4& b) { return make_float4(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w); }
	inline void operator/=(float4& a, const float4& b) { a.x /= b.x;	a.y /= b.y;	a.z /= b.z;	a.w /= b.w; }
	inline float4 operator/(const float4& a, float b) { return make_float4(a.x / b, a.y / b, a.z / b, a.w / b); }
	inline void operator/=(float4& a, float b) { a.x /= b;	a.y /= b;	a.z /= b;	a.w /= b; }
	inline float4 operator/(float b, const float4& a) { return make_float4(b / a.x, b / a.y, b / a.z, b / a.w); }

	inline float rsqrtf(float a) { return (1.0f / std::sqrt(a)); }

	inline float2 fminf(const float2& a, const float2& b) { return make_float2(std::fminf(a.x, b.x), std::fminf(a.y, b.y)); }
	inline float3 fminf(const float3& a, const float3& b) { return make_float3(std::fminf(a.x, b.x), std::fminf(a.y, b.y), std::fminf(a.z, b.z)); }
	inline float4 fminf(const float4& a, const float4& b) { return make_float4(std::fminf(a.x, b.x), std::fminf(a.y, b.y), std::fminf(a.z, b.z), std::fminf(a.w, b.w)); }
	inline int2 min(const int2& a, const int2& b) { return make_int2(std::min(a.x, b.x), std::min(a.y, b.y)); }
	inline int3 min(const int3& a, const int3& b) { return make_int3(std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z)); }
	inline int4 min(const int4& a, const int4& b) { return make_int4(std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z), std::min(a.w, b.w)); }
	inline uint2 min(const uint2& a, const uint2& b) { return make_uint2(std::min(a.x, b.x), std::min(a.y, b.y)); }
	inline uint3 min(const uint3& a, const uint3& b) { return make_uint3(std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z)); }
	inline uint4 min(const uint4& a, const uint4& b) { return make_uint4(std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z), std::min(a.w, b.w)); }

	inline float2 fmaxf(const float2& a, const float2& b) { return make_float2(std::fmaxf(a.x, b.x), std::fmaxf(a.y, b.y)); }
	inline float3 fmaxf(const float3& a, const float3& b) { return make_float3(std::fmaxf(a.x, b.x), std::fmaxf(a.y, b.y), std::fmaxf(a.z, b.z)); }
	inline float4 fmaxf(const float4& a, const float4& b) { return make_float4(std::fmaxf(a.x, b.x), std::fmaxf(a.y, b.y), std::fmaxf(a.z, b.z), std::fmaxf(a.w, b.w)); }
	inline int2 max(const int2& a, const int2& b) { return make_int2(std::max(a.x, b.x), std::max(a.y, b.y)); }
	inline int3 max(const int3& a, const int3& b) { return make_int3(std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z)); }
	inline int4 max(const int4& a, const int4& b) { return make_int4(std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z), std::max(a.w, b.w)); }
	inline uint2 max(const uint2& a, const uint2& b) { return make_uint2(std::max(a.x, b.x), std::max(a.y, b.y)); }
	inline uint3 max(const uint3& a, const uint3& b) { return make_uint3(std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z)); }
	inline uint4 max(const uint4& a, const uint4& b) { return make_uint4(std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z), std::max(a.w, b.w)); }

	inline float lerp(float a, float b, float t) { return a + t * (b - a); }
	inline float2 lerp(const float2& a, const float2& b, float t) { return a + t * (b - a); }
	inline float3 lerp(const float3& a, const float3& b, float t) { return a + t * (b - a); }
	inline float4 lerp(const float4& a, const float4& b, float t) { return a + t * (b - a); }

	inline float clamp(float f, float a, float b) { return std::fmaxf(a, std::fminf(f, b)); }
	inline int clamp(int f, int a, int b) { return std::max(a, std::min(f, b)); }
	inline uint clamp(uint f, uint a, uint b) { return std::max(a, std::min(f, b)); }
	inline float2 clamp(const float2& v, float a, float b) { return make_float2(clamp(v.x, a, b), clamp(v.y, a, b)); }
	inline float2 clamp(const float2& v, const float2& a, const float2& b) { return make_float2(clamp(v.x, a.x, b.x), clamp(v.y, a.y, b.y)); }
	inline float3 clamp(const float3& v, float a, float b) { return make_float3(clamp(v.x, a, b), clamp(v.y, a, b), clamp(v.z, a, b)); }
	inline float3 clamp(const float3& v, const float3& a, const float3& b) { return make_float3(clamp(v.x, a.x, b.x), clamp(v.y, a.y, b.y), clamp(v.z, a.z, b.z)); }
	inline float4 clamp(const float4& v, float a, float b) { return make_float4(clamp(v.x, a, b), clamp(v.y, a, b), clamp(v.z, a, b), clamp(v.w, a, b)); }
	inline float4 clamp(const float4& v, const float4& a, const float4& b) { return make_float4(clamp(v.x, a.x, b.x), clamp(v.y, a.y, b.y), clamp(v.z, a.z, b.z), clamp(v.w, a.w, b.w)); }
	inline int2 clamp(const int2& v, int a, int b) { return make_int2(clamp(v.x, a, b), clamp(v.y, a, b)); }
	inline int2 clamp(const int2& v, const int2& a, const int2& b) { return make_int2(clamp(v.x, a.x, b.x), clamp(v.y, a.y, b.y)); }
	inline int3 clamp(const int3& v, int a, int b) { return make_int3(clamp(v.x, a, b), clamp(v.y, a, b), clamp(v.z, a, b)); }
	inline int3 clamp(const int3& v, const int3& a, const int3& b) { return make_int3(clamp(v.x, a.x, b.x), clamp(v.y, a.y, b.y), clamp(v.z, a.z, b.z)); }
	inline int4 clamp(const int4& v, int a, int b) { return make_int4(clamp(v.x, a, b), clamp(v.y, a, b), clamp(v.z, a, b), clamp(v.w, a, b)); }
	inline int4 clamp(const int4& v, const int4& a, const int4& b) { return make_int4(clamp(v.x, a.x, b.x), clamp(v.y, a.y, b.y), clamp(v.z, a.z, b.z), clamp(v.w, a.w, b.w)); }
	inline uint2 clamp(const uint2& v, uint a, uint b) { return make_uint2(clamp(v.x, a, b), clamp(v.y, a, b)); }
	inline uint2 clamp(const uint2& v, const uint2& a, const uint2& b) { return make_uint2(clamp(v.x, a.x, b.x), clamp(v.y, a.y, b.y)); }
	inline uint3 clamp(const uint3& v, uint a, uint b) { return make_uint3(clamp(v.x, a, b), clamp(v.y, a, b), clamp(v.z, a, b)); }
	inline uint3 clamp(const uint3& v, const uint3& a, const uint3& b) { return make_uint3(clamp(v.x, a.x, b.x), clamp(v.y, a.y, b.y), clamp(v.z, a.z, b.z)); }
	inline uint4 clamp(const uint4& v, uint a, uint b) { return make_uint4(clamp(v.x, a, b), clamp(v.y, a, b), clamp(v.z, a, b), clamp(v.w, a, b)); }
	inline uint4 clamp(const uint4& v, const uint4& a, const uint4& b) { return make_uint4(clamp(v.x, a.x, b.x), clamp(v.y, a.y, b.y), clamp(v.z, a.z, b.z), clamp(v.w, a.w, b.w)); }

	inline float dot(const float2& a, const float2& b) { return a.x * b.x + a.y * b.y; }
	inline float dot(const float3& a, const float3& b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
	inline float dot(const float4& a, const float4& b) { return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w; }
	inline int dot(const int2& a, const int2& b) { return a.x * b.x + a.y * b.y; }
	inline int dot(const int3& a, const int3& b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
	inline int dot(const int4& a, const int4& b) { return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w; }
	inline uint dot(const uint2& a, const uint2& b) { return a.x * b.x + a.y * b.y; }
	inline uint dot(const uint3& a, const uint3& b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
	inline uint dot(const uint4& a, const uint4& b) { return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w; }

	inline float sqrLength(const float2& v) { return dot(v, v); }
	inline float sqrLength(const float3& v) { return dot(v, v); }
	inline float sqrLength(const float4& v) { return dot(v, v); }

	inline float length(const float2& v) { return sqrtf(dot(v, v)); }
	inline float length(const float3& v) { return sqrtf(dot(v, v)); }
	inline float length(const float4& v) { return sqrtf(dot(v, v)); }

	inline float length(const int2& v) { return sqrtf(static_cast<float>(dot(v, v))); }
	inline float length(const int3& v) { return sqrtf(static_cast<float>(dot(v, v))); }
	inline float length(const int4& v) { return sqrtf(static_cast<float>(dot(v, v))); }

	inline float2 normalize(const float2& v) { float invLen = rsqrtf(dot(v, v)); return v * invLen; }
	inline float3 normalize(const float3& v) { float invLen = rsqrtf(dot(v, v)); return v * invLen; }
	inline float4 normalize(const float4& v) { float invLen = rsqrtf(dot(v, v)); return v * invLen; }

	inline uint dominantAxis(const float2& v) { float x = std::fabs(v.x), y = std::fabs(v.y); return x > y ? 0 : 1; } // for coherent grid traversal
	inline uint dominantAxis(const float3& v) { float x = std::fabs(v.x), y = std::fabs(v.y), z = std::fabs(v.z); float m = std::max(std::max(x, y), z); return m == x ? 0 : (m == y ? 1 : 2); }

	inline float2 floorf(const float2& v) { return make_float2(std::floorf(v.x), std::floorf(v.y)); }
	inline float3 floorf(const float3& v) { return make_float3(std::floorf(v.x), std::floorf(v.y), std::floorf(v.z)); }
	inline float4 floorf(const float4& v) { return make_float4(std::floorf(v.x), std::floorf(v.y), std::floorf(v.z), std::floorf(v.w)); }

	inline float fracf(float v) { return v - std::floorf(v); }
	inline float2 fracf(const float2& v) { return make_float2(fracf(v.x), fracf(v.y)); }
	inline float3 fracf(const float3& v) { return make_float3(fracf(v.x), fracf(v.y), fracf(v.z)); }
	inline float4 fracf(const float4& v) { return make_float4(fracf(v.x), fracf(v.y), fracf(v.z), fracf(v.w)); }

	inline float2 fmodf(const float2& a, const float2& b) { return make_float2(std::fmodf(a.x, b.x), std::fmodf(a.y, b.y)); }
	inline float3 fmodf(const float3& a, const float3& b) { return make_float3(std::fmodf(a.x, b.x), std::fmodf(a.y, b.y), std::fmodf(a.z, b.z)); }
	inline float4 fmodf(const float4& a, const float4& b) { return make_float4(std::fmodf(a.x, b.x), std::fmodf(a.y, b.y), std::fmodf(a.z, b.z), std::fmodf(a.w, b.w)); }

	inline float2 fabs(const float2& v) { return make_float2(std::fabs(v.x), std::fabs(v.y)); }
	inline float3 fabs(const float3& v) { return make_float3(std::fabs(v.x), std::fabs(v.y), std::fabs(v.z)); }
	inline float4 fabs(const float4& v) { return make_float4(std::fabs(v.x), std::fabs(v.y), std::fabs(v.z), std::fabs(v.w)); }
	inline int2 abs(const int2& v) { return make_int2(std::abs(v.x), std::abs(v.y)); }
	inline int3 abs(const int3& v) { return make_int3(std::abs(v.x), std::abs(v.y), std::abs(v.z)); }
	inline int4 abs(const int4& v) { return make_int4(std::abs(v.x), std::abs(v.y), std::abs(v.z), std::abs(v.w)); }

	inline float3 reflect(const float3& i, const float3& n) { return i - 2.0f * n * dot(n, i); }

	inline float3 cross(const float3& a, const float3& b) { return make_float3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x); }

	inline float smoothstep(float a, float b, float x)
	{
		float y = clamp((x - a) / (b - a), 0.0f, 1.0f);
		return (y * y * (3.0f - (2.0f * y)));
	}
	inline float2 smoothstep(float2 a, float2 b, float2 x)
	{
		float2 y = clamp((x - a) / (b - a), 0.0f, 1.0f);
		return (y * y * (make_float2(3.0f) - (make_float2(2.0f) * y)));
	}
	inline float3 smoothstep(float3 a, float3 b, float3 x)
	{
		float3 y = clamp((x - a) / (b - a), 0.0f, 1.0f);
		return (y * y * (make_float3(3.0f) - (make_float3(2.0f) * y)));
	}
	inline float4 smoothstep(float4 a, float4 b, float4 x)
	{
		float4 y = clamp((x - a) / (b - a), 0.0f, 1.0f);
		return (y * y * (make_float4(3.0f) - (make_float4(2.0f) * y)));
	}

	// axis aligned bounding box class
	class aabb
	{
	public:
		aabb() = default;
		aabb(__m128 a, __m128 b) { bmin4 = a, bmax4 = b; bmin[3] = bmax[3] = 0; }
		aabb(float3 a, float3 b) { bmin[0] = a.x, bmin[1] = a.y, bmin[2] = a.z, bmin[3] = 0, bmax[0] = b.x, bmax[1] = b.y, bmax[2] = b.z, bmax[3] = 0; }
		__inline void Reset() { bmin4 = _mm_set_ps1(1e34f), bmax4 = _mm_set_ps1(-1e34f); }
		bool Contains(const __m128& p) const
		{
			union { __m128 va4; float va[4]; };
			union { __m128 vb4; float vb[4]; };
			va4 = _mm_sub_ps(p, bmin4), vb4 = _mm_sub_ps(bmax4, p);
			return ((va[0] >= 0) && (va[1] >= 0) && (va[2] >= 0) &&
				(vb[0] >= 0) && (vb[1] >= 0) && (vb[2] >= 0));
		}
		void Grow(const aabb& bb) { bmin4 = _mm_min_ps(bmin4, bb.bmin4); bmax4 = _mm_max_ps(bmax4, bb.bmax4); }
		void Grow(const __m128& p) { bmin4 = _mm_min_ps(bmin4, p); bmax4 = _mm_max_ps(bmax4, p); }
		void Grow(const __m128 min4, const __m128 max4) { bmin4 = _mm_min_ps(bmin4, min4); bmax4 = _mm_max_ps(bmax4, max4); }
		void Grow(const float3& p) { __m128 p4 = _mm_setr_ps(p.x, p.y, p.z, 0); Grow(p4); }
		aabb Union(const aabb& bb) const { aabb r; r.bmin4 = _mm_min_ps(bmin4, bb.bmin4), r.bmax4 = _mm_max_ps(bmax4, bb.bmax4); return r; }
		static aabb Union(const aabb& a, const aabb& b) { aabb r; r.bmin4 = _mm_min_ps(a.bmin4, b.bmin4), r.bmax4 = _mm_max_ps(a.bmax4, b.bmax4); return r; }
		aabb Intersection(const aabb& bb) const { aabb r; r.bmin4 = _mm_max_ps(bmin4, bb.bmin4), r.bmax4 = _mm_min_ps(bmax4, bb.bmax4); return r; }
		float Extend(const int axis) const { return bmax[axis] - bmin[axis]; }
		float Minimum(const int axis) const { return bmin[axis]; }
		float Maximum(const int axis) const { return bmax[axis]; }
		float Area() const
		{
			union { __m128 e4; float e[4]; };
			e4 = _mm_sub_ps(bmax4, bmin4);
			return std::max(0.0f, e[0] * e[1] + e[0] * e[2] + e[1] * e[2]);
		}
		int LongestAxis() const
		{
			int a = 0;
			if (Extend(1) > Extend(0)) a = 1;
			if (Extend(2) > Extend(a)) a = 2;
			return a;
		}
		// data members
		union
		{
			struct
			{
				union { __m128 bmin4; float bmin[4]; struct { float3 bmin3; }; };
				union { __m128 bmax4; float bmax[4]; struct { float3 bmax3; }; };
			};
			__m128 bounds[2] = { _mm_set_ps(1e34f, 1e34f, 1e34f, 0), _mm_set_ps(-1e34f, -1e34f, -1e34f, 0) };
		};

		void SetBounds(const __m128 min4, const __m128 max4) { bmin4 = min4; bmax4 = max4; }
		__m128 Center() const { return _mm_mul_ps(_mm_add_ps(bmin4, bmax4), _mm_set_ps1(0.5f)); }
		float Center(uint axis) const { return (bmin[axis] + bmax[axis]) * 0.5f; }
	};

	// matrix class
	class mat4
	{
	public:
		mat4() = default;
		float cell[16] = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
		float& operator [] (const int idx) { return cell[idx]; }
		float operator()(const int i, const int j) const { return cell[i * 4 + j]; }
		float& operator()(const int i, const int j) { return cell[i * 4 + j]; }
		mat4& operator += (const mat4& a);
		bool operator==(const mat4& m) const;
		[[nodiscard]] float3 GetTranslation() const;

		static mat4 FromColumnMajor(const mat4& T);
		constexpr static mat4 Identity() { return mat4{}; }
		static mat4 ZeroMatrix() { mat4 r; memset(r.cell, 0, 64); return r; }
		static mat4 RotateX(const float a) { mat4 r; r.cell[5] = cosf(a); r.cell[6] = -sinf(a); r.cell[9] = sinf(a); r.cell[10] = cosf(a); return r; };
		static mat4 RotateY(const float a) { mat4 r; r.cell[0] = cosf(a); r.cell[2] = sinf(a); r.cell[8] = -sinf(a); r.cell[10] = cosf(a); return r; };
		static mat4 RotateZ(const float a) { mat4 r; r.cell[0] = cosf(a); r.cell[1] = -sinf(a); r.cell[4] = sinf(a); r.cell[5] = cosf(a); return r; };
		static mat4 Scale(const float s) { mat4 r; r.cell[0] = r.cell[5] = r.cell[10] = s; return r; }
		static mat4 Scale(const float3 s) { mat4 r; r.cell[0] = s.x, r.cell[5] = s.y, r.cell[10] = s.z; return r; }
		static mat4 Scale(const float4 s) { mat4 r; r.cell[0] = s.x, r.cell[5] = s.y, r.cell[10] = s.z, r.cell[15] = s.w; return r; }
		static mat4 Rotate(const float3& u, const float a) { return Rotate(u.x, u.y, u.z, a); }
		static mat4 Rotate(const float x, const float y, const float z, const float a);

		static mat4 LookAt(const float3 P, const float3 T);

		static mat4 LookAt(const float3& pos, const float3& look, const float3& up);
		static mat4 Translate(const float x, const float y, const float z) { mat4 r; r.cell[3] = x; r.cell[7] = y; r.cell[11] = z; return r; };
		static mat4 Translate(const float3 P) { mat4 r; r.cell[3] = P.x; r.cell[7] = P.y; r.cell[11] = P.z; return r; };
		float Trace3() const { return cell[0] + cell[5] + cell[10]; }
		[[nodiscard]] mat4 Transposed() const;
		[[nodiscard]] mat4 Inverted() const;
		[[nodiscard]] mat4 Inverted3x3() const;

		[[nodiscard]] float3 TransformVector(const float3& v) const;
		[[nodiscard]] float3 TransformPoint(const float3& v) const;
	};

	mat4 operator * (const mat4& a, const mat4& b);
	mat4 operator + (const mat4& a, const mat4& b);
	mat4 operator * (const mat4& a, const float s);
	mat4 operator * (const float s, const mat4& a);
	bool operator == (const mat4& a, const mat4& b);
	bool operator != (const mat4& a, const mat4& b);
	float4 operator * (const mat4& a, const float4& b);
	float4 operator * (const float4& a, const mat4& b);

	float3 TransformPosition(const float3& a, const mat4& M);
	float3 TransformVector(const float3& a, const mat4& M);

	class quat // based on https://github.com/adafruit
	{
	public:
		quat() = default;
		quat(float _w, float _x, float _y, float _z) : w(_w), x(_x), y(_y), z(_z) {}
		quat(float _w, float3 v) : w(_w), x(v.x), y(v.y), z(v.z) {}
		float magnitude() const { return sqrtf(w * w + x * x + y * y + z * z); }
		void normalize() { float m = magnitude(); *this = this->scale(1 / m); }
		quat conjugate() const { return quat(w, -x, -y, -z); }
		void fromAxisAngle(const float3& axis, float theta);
		void fromMatrix(const mat4& m);
		void toAxisAngle(float3& axis, float& angle) const;

		mat4 toMatrix() const;
		float3 toEuler() const;
		float3 toAngularVelocity(float dt) const;

		float3 rotateVector(const float3& v) const;

		quat operator * (const quat& q) const;

		static quat slerp(const quat& a, const quat& b, const float t);
		quat operator + (const quat& q) const { return quat(w + q.w, x + q.x, y + q.y, z + q.z); }
		quat operator - (const quat& q) const { return quat(w - q.w, x - q.x, y - q.y, z - q.z); }
		quat operator / (float s) const { return quat(w / s, x / s, y / s, z / s); }
		quat operator * (float s) const { return scale(s); }
		quat scale(float s) const { return quat(w * s, x * s, y * s, z * s); }
		float w = 1, x = 0, y = 0, z = 0;
	};
};