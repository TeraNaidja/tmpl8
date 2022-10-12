#pragma once

template <typename TDataType>
struct TVec2
{
	constexpr TVec2() = default;

	constexpr explicit TVec2(TDataType value) : x(value), y(value)
	{
	}

	constexpr TVec2(TDataType a, TDataType b) : x(a), y(b)
	{
	}

	constexpr TDataType& operator[](const int n) { return cell[n]; }

	template <typename TOtherDataType>
	constexpr explicit TVec2(TVec2<TOtherDataType> other) : x(static_cast<TDataType>(other.x)), y(static_cast<TDataType>(other.y))
	{
	}

	constexpr TVec2 operator+(TVec2 rhs) const { return TVec2(x + rhs.x, y + rhs.y); }
	constexpr TVec2 operator-(TVec2 rhs) const { return TVec2(x - rhs.x, y - rhs.y); }
	constexpr TVec2 operator*(TVec2 rhs) const { return TVec2(x * rhs.x, y * rhs.y); }
	constexpr TVec2 operator*(TDataType rhs) const { return TVec2(x * rhs, y * rhs); }
	constexpr TVec2 operator/(TVec2 rhs) const { return TVec2(x / rhs.x, y / rhs.y); }
	constexpr TVec2 operator/(TDataType rhs) const { return TVec2(x / rhs, y / rhs); }

	constexpr TVec2& operator+=(TVec2 rhs)
	{
		x += rhs.x;
		y += rhs.y;
		return *this;
	}

	constexpr TVec2& operator-=(TVec2 rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}

	constexpr TVec2& operator*=(TVec2 rhs)
	{
		x *= rhs.x;
		y *= rhs.y;
		return *this;
	}

	constexpr TVec2& operator*=(TDataType rhs)
	{
		x *= rhs;
		y *= rhs;
		return *this;
	}

	constexpr TVec2& operator/=(TDataType rhs)
	{
		x /= rhs;
		y /= rhs;
		return *this;
	}

	constexpr TVec2 operator-() { return TVec2(-x, -y); }

	union
	{
		struct
		{
			TDataType x, y;
		};

		TDataType cell[2];
	};
};

template <typename TDataType>
struct TVec3
{
	constexpr TVec3() = default;

	constexpr explicit TVec3(TDataType value) : x(value), y(value), z(value)
	{
	}

	constexpr TVec3(TDataType a, TDataType b, TDataType c) : x(a), y(b), z(c)
	{
	}

	constexpr TVec3(TVec2<TDataType> a, TDataType b) : x(a.x), y(a.y), z(b)
	{
	}

	template <typename TOtherDataType>
	constexpr explicit TVec3(TVec3<TOtherDataType> other) : x(static_cast<TDataType>(other.x)), y(static_cast<TDataType>(other.y)), z(static_cast<TDataType>(other.z))
	{
	}

	constexpr TVec3 operator+(TVec3 rhs) const { return TVec3(x + rhs.x, y + rhs.y, z + rhs.z); }
	constexpr TVec3 operator-(TVec3 rhs) const { return TVec3(x - rhs.x, y - rhs.y, z - rhs.z); }
	constexpr TVec3 operator*(TVec3 rhs) const { return TVec3(x * rhs.x, y * rhs.y, z * rhs.z); }
	constexpr TVec3 operator*(TDataType rhs) const { return TVec3(x * rhs, y * rhs, z * rhs); }
	constexpr TVec3 operator/(TVec3 rhs) const { return TVec3(x / rhs.x, y / rhs.y, z / rhs.z); }
	constexpr TVec3 operator/(TDataType rhs) const { return TVec3(x / rhs, y / rhs, z / rhs); }

	constexpr TVec3& operator+=(TVec3 rhs)
	{
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		return *this;
	}

	constexpr TVec3& operator-=(TVec3 rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		return *this;
	}

	constexpr TVec3& operator*=(TVec3 rhs)
	{
		x *= rhs.x;
		y *= rhs.y;
		z *= rhs.z;
		return *this;
	}

	constexpr TVec3& operator*=(TDataType rhs)
	{
		x *= rhs;
		y *= rhs;
		z *= rhs;
		return *this;
	}

	constexpr TVec3& operator/=(TDataType rhs)
	{
		x /= rhs;
		y /= rhs;
		z /= rhs;
		return *this;
	}

	constexpr TVec3 operator-() { return TVec3(-x, -y, -z); }

	union
	{
		struct
		{
			TDataType x, y, z;
		};

		TDataType cell[3];
		TVec2<TDataType> xy;
	};
};

template <typename TDataType>
struct TVec4
{
	TVec4() = default;

	constexpr explicit TVec4(TDataType value) : x(value), y(value), z(value), w(value)
	{
	}

	constexpr TVec4(TDataType a, TDataType b, TDataType c, TDataType d) : x(a), y(b), z(c), w(d)
	{
	}

	constexpr TVec4(TVec2<TDataType> a, TDataType b, TDataType c) : x(a.x), y(a.y), z(b), w(c)
	{
	}

	constexpr TVec4(TVec3<TDataType> a, TDataType b) : x(a.x), y(a.y), z(a.z), w(b)
	{
	}

	template <typename TOtherDataType>
	constexpr explicit TVec4(TVec4<TOtherDataType> other) : x(static_cast<TDataType>(other.x)), y(static_cast<TDataType>(other.y)), z(static_cast<TDataType>(other.z)), w(static_cast<TDataType>(other.w))
	{
	}

	constexpr TVec4 operator+(TVec4 rhs) const { return TVec4(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w); }
	constexpr TVec4 operator-(TVec4 rhs) const { return TVec4(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w); }
	constexpr TVec4 operator*(TVec4 rhs) const { return TVec4(x * rhs.x, y * rhs.y, z * rhs.z, w * rhs.w); }
	constexpr TVec4 operator*(TDataType rhs) const { return TVec4(x * rhs, y * rhs, z * rhs, w * rhs); }
	constexpr TVec4 operator/(TVec4 rhs) const { return TVec4(x / rhs.x, y / rhs.y, z / rhs.z, w / rhs.w); }
	constexpr TVec4 operator/(TDataType rhs) const { return TVec4(x / rhs, y / rhs, z / rhs, w / rhs); }

	constexpr TVec4& operator+=(TVec4 rhs)
	{
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		w += rhs.w;
		return *this;
	}

	constexpr TVec4& operator-=(TVec4 rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		w -= rhs.w;
		return *this;
	}

	constexpr TVec4& operator*=(TVec4 rhs)
	{
		x *= rhs.x;
		y *= rhs.y;
		z *= rhs.z;
		w *= rhs.w;
		return *this;
	}

	constexpr TVec4& operator*=(TDataType rhs)
	{
		x *= rhs;
		y *= rhs;
		z *= rhs;
		w *= rhs;
		return *this;
	}

	constexpr TVec4& operator/=(TDataType rhs)
	{
		x /= rhs;
		y /= rhs;
		z /= rhs;
		w /= rhs;
		return *this;
	}

	constexpr TVec4 operator-() { return TVec4(-x, -y, -z, -w); }

	union
	{
		struct
		{
			TDataType x, y, z, w;
		};

		TDataType cell[4];
		TVec3<TDataType> xyz;
	};
};

using int2 = TVec2<int>;
using uint2 = TVec2<uint>;
using float2 = TVec2<float>;

using int3 = TVec3<int>;
using uint3 = TVec3<uint>;
using float3 = TVec3<float>;

using int4 = TVec4<int>;
using uint4 = TVec4<uint>;
using float4 = TVec4<float>;
using uchar4 = TVec4<uchar>;

inline int2 operator <<(const int2& a, int b) { return int2(a.x << b, a.y << b); }
inline int2 operator >>(const int2& a, int b) { return int2(a.x >> b, a.y >> b); }
inline int3 operator <<(const int3& a, int b) { return int3(a.x << b, a.y << b, a.z << b); }
inline int3 operator >>(const int3& a, int b) { return int3(a.x >> b, a.y >> b, a.z >> b); }
inline int4 operator <<(const int4& a, int b) { return int4(a.x << b, a.y << b, a.z << b, a.w << b); }
inline int4 operator >>(const int4& a, int b) { return int4(a.x >> b, a.y >> b, a.z >> b, a.w >> b); }

inline float rsqrtf(float a) { return (1.0f / std::sqrt(a)); }

inline float2 fminf(const float2& a, const float2& b) { return float2(std::fminf(a.x, b.x), std::fminf(a.y, b.y)); }
inline float3 fminf(const float3& a, const float3& b) { return float3(std::fminf(a.x, b.x), std::fminf(a.y, b.y), std::fminf(a.z, b.z)); }
inline float4 fminf(const float4& a, const float4& b) { return float4(std::fminf(a.x, b.x), std::fminf(a.y, b.y), std::fminf(a.z, b.z), std::fminf(a.w, b.w)); }
inline int2 min(const int2& a, const int2& b) { return int2(std::min(a.x, b.x), std::min(a.y, b.y)); }
inline int3 min(const int3& a, const int3& b) { return int3(std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z)); }
inline int4 min(const int4& a, const int4& b) { return int4(std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z), std::min(a.w, b.w)); }
inline uint2 min(const uint2& a, const uint2& b) { return uint2(std::min(a.x, b.x), std::min(a.y, b.y)); }
inline uint3 min(const uint3& a, const uint3& b) { return uint3(std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z)); }
inline uint4 min(const uint4& a, const uint4& b) { return uint4(std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z), std::min(a.w, b.w)); }

inline float2 fmaxf(const float2& a, const float2& b) { return float2(std::fmaxf(a.x, b.x), std::fmaxf(a.y, b.y)); }
inline float3 fmaxf(const float3& a, const float3& b) { return float3(std::fmaxf(a.x, b.x), std::fmaxf(a.y, b.y), std::fmaxf(a.z, b.z)); }
inline float4 fmaxf(const float4& a, const float4& b) { return float4(std::fmaxf(a.x, b.x), std::fmaxf(a.y, b.y), std::fmaxf(a.z, b.z), std::fmaxf(a.w, b.w)); }
inline int2 max(const int2& a, const int2& b) { return int2(std::max(a.x, b.x), std::max(a.y, b.y)); }
inline int3 max(const int3& a, const int3& b) { return int3(std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z)); }
inline int4 max(const int4& a, const int4& b) { return int4(std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z), std::max(a.w, b.w)); }
inline uint2 max(const uint2& a, const uint2& b) { return uint2(std::max(a.x, b.x), std::max(a.y, b.y)); }
inline uint3 max(const uint3& a, const uint3& b) { return uint3(std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z)); }
inline uint4 max(const uint4& a, const uint4& b) { return uint4(std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z), std::max(a.w, b.w)); }

inline float lerp(float a, float b, float t) { return a + t * (b - a); }
inline float2 lerp(const float2& a, const float2& b, float t) { return a + (b - a) * t; }
inline float3 lerp(const float3& a, const float3& b, float t) { return a + (b - a) * t; }
inline float4 lerp(const float4& a, const float4& b, float t) { return a + (b - a) * t; }

inline float clamp(float f, float a, float b) { return std::fmaxf(a, std::fminf(f, b)); }
inline int clamp(int f, int a, int b) { return std::max(a, std::min(f, b)); }
inline uint clamp(uint f, uint a, uint b) { return std::max(a, std::min(f, b)); }
inline float2 clamp(const float2& v, float a, float b) { return float2(clamp(v.x, a, b), clamp(v.y, a, b)); }
inline float2 clamp(const float2& v, const float2& a, const float2& b) { return float2(clamp(v.x, a.x, b.x), clamp(v.y, a.y, b.y)); }
inline float3 clamp(const float3& v, float a, float b) { return float3(clamp(v.x, a, b), clamp(v.y, a, b), clamp(v.z, a, b)); }
inline float3 clamp(const float3& v, const float3& a, const float3& b) { return float3(clamp(v.x, a.x, b.x), clamp(v.y, a.y, b.y), clamp(v.z, a.z, b.z)); }
inline float4 clamp(const float4& v, float a, float b) { return float4(clamp(v.x, a, b), clamp(v.y, a, b), clamp(v.z, a, b), clamp(v.w, a, b)); }
inline float4 clamp(const float4& v, const float4& a, const float4& b) { return float4(clamp(v.x, a.x, b.x), clamp(v.y, a.y, b.y), clamp(v.z, a.z, b.z), clamp(v.w, a.w, b.w)); }
inline int2 clamp(const int2& v, int a, int b) { return int2(clamp(v.x, a, b), clamp(v.y, a, b)); }
inline int2 clamp(const int2& v, const int2& a, const int2& b) { return int2(clamp(v.x, a.x, b.x), clamp(v.y, a.y, b.y)); }
inline int3 clamp(const int3& v, int a, int b) { return int3(clamp(v.x, a, b), clamp(v.y, a, b), clamp(v.z, a, b)); }
inline int3 clamp(const int3& v, const int3& a, const int3& b) { return int3(clamp(v.x, a.x, b.x), clamp(v.y, a.y, b.y), clamp(v.z, a.z, b.z)); }
inline int4 clamp(const int4& v, int a, int b) { return int4(clamp(v.x, a, b), clamp(v.y, a, b), clamp(v.z, a, b), clamp(v.w, a, b)); }
inline int4 clamp(const int4& v, const int4& a, const int4& b) { return int4(clamp(v.x, a.x, b.x), clamp(v.y, a.y, b.y), clamp(v.z, a.z, b.z), clamp(v.w, a.w, b.w)); }
inline uint2 clamp(const uint2& v, uint a, uint b) { return uint2(clamp(v.x, a, b), clamp(v.y, a, b)); }
inline uint2 clamp(const uint2& v, const uint2& a, const uint2& b) { return uint2(clamp(v.x, a.x, b.x), clamp(v.y, a.y, b.y)); }
inline uint3 clamp(const uint3& v, uint a, uint b) { return uint3(clamp(v.x, a, b), clamp(v.y, a, b), clamp(v.z, a, b)); }
inline uint3 clamp(const uint3& v, const uint3& a, const uint3& b) { return uint3(clamp(v.x, a.x, b.x), clamp(v.y, a.y, b.y), clamp(v.z, a.z, b.z)); }
inline uint4 clamp(const uint4& v, uint a, uint b) { return uint4(clamp(v.x, a, b), clamp(v.y, a, b), clamp(v.z, a, b), clamp(v.w, a, b)); }
inline uint4 clamp(const uint4& v, const uint4& a, const uint4& b) { return uint4(clamp(v.x, a.x, b.x), clamp(v.y, a.y, b.y), clamp(v.z, a.z, b.z), clamp(v.w, a.w, b.w)); }

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

inline float2 normalize(const float2& v)
{
	float invLen = rsqrtf(dot(v, v));
	return v * invLen;
}

inline float3 normalize(const float3& v)
{
	float invLen = rsqrtf(dot(v, v));
	return v * invLen;
}

inline float4 normalize(const float4& v)
{
	float invLen = rsqrtf(dot(v, v));
	return v * invLen;
}

inline uint dominantAxis(const float2& v)
{
	float x = std::fabs(v.x), y = std::fabs(v.y);
	return x > y ? 0 : 1;
} // for coherent grid traversal
inline uint dominantAxis(const float3& v)
{
	float x = std::fabs(v.x), y = std::fabs(v.y), z = std::fabs(v.z);
	float m = std::max(std::max(x, y), z);
	return m == x ? 0 : (m == y ? 1 : 2);
}

inline float2 floorf(const float2& v) { return float2(std::floorf(v.x), std::floorf(v.y)); }
inline float3 floorf(const float3& v) { return float3(std::floorf(v.x), std::floorf(v.y), std::floorf(v.z)); }
inline float4 floorf(const float4& v) { return float4(std::floorf(v.x), std::floorf(v.y), std::floorf(v.z), std::floorf(v.w)); }

inline float fracf(float v) { return v - std::floorf(v); }
inline float2 fracf(const float2& v) { return float2(fracf(v.x), fracf(v.y)); }
inline float3 fracf(const float3& v) { return float3(fracf(v.x), fracf(v.y), fracf(v.z)); }
inline float4 fracf(const float4& v) { return float4(fracf(v.x), fracf(v.y), fracf(v.z), fracf(v.w)); }

inline float2 fmodf(const float2& a, const float2& b) { return float2(std::fmodf(a.x, b.x), std::fmodf(a.y, b.y)); }
inline float3 fmodf(const float3& a, const float3& b) { return float3(std::fmodf(a.x, b.x), std::fmodf(a.y, b.y), std::fmodf(a.z, b.z)); }
inline float4 fmodf(const float4& a, const float4& b) { return float4(std::fmodf(a.x, b.x), std::fmodf(a.y, b.y), std::fmodf(a.z, b.z), std::fmodf(a.w, b.w)); }

inline float2 fabs(const float2& v) { return float2(std::fabs(v.x), std::fabs(v.y)); }
inline float3 fabs(const float3& v) { return float3(std::fabs(v.x), std::fabs(v.y), std::fabs(v.z)); }
inline float4 fabs(const float4& v) { return float4(std::fabs(v.x), std::fabs(v.y), std::fabs(v.z), std::fabs(v.w)); }
inline int2 abs(const int2& v) { return int2(std::abs(v.x), std::abs(v.y)); }
inline int3 abs(const int3& v) { return int3(std::abs(v.x), std::abs(v.y), std::abs(v.z)); }
inline int4 abs(const int4& v) { return int4(std::abs(v.x), std::abs(v.y), std::abs(v.z), std::abs(v.w)); }

inline float3 reflect(const float3& i, const float3& n) { return i - (n * 2.0f * dot(n, i)); }

inline float3 cross(const float3& a, const float3& b) { return float3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x); }

inline float smoothstep(float a, float b, float x)
{
	float y = clamp((x - a) / (b - a), 0.0f, 1.0f);
	return (y * y * (3.0f - (2.0f * y)));
}

inline float2 smoothstep(float2 a, float2 b, float2 x)
{
	float2 y = clamp((x - a) / (b - a), 0.0f, 1.0f);
	return (y * y * (float2(3.0f) - (float2(2.0f) * y)));
}

inline float3 smoothstep(float3 a, float3 b, float3 x)
{
	float3 y = clamp((x - a) / (b - a), 0.0f, 1.0f);
	return (y * y * (float3(3.0f) - (float3(2.0f) * y)));
}

inline float4 smoothstep(float4 a, float4 b, float4 x)
{
	float4 y = clamp((x - a) / (b - a), 0.0f, 1.0f);
	return (y * y * (float4(3.0f) - (float4(2.0f) * y)));
}

// matrix class
class mat4
{
public:
	mat4() = default;
	float cell[16] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
	float& operator [](const int idx) { return cell[idx]; }
	float operator()(const int i, const int j) const { return cell[i * 4 + j]; }
	float& operator()(const int i, const int j) { return cell[i * 4 + j]; }
	mat4& operator +=(const mat4& a);
	[[nodiscard]] float3 GetTranslation() const;

	static mat4 FromColumnMajor(const mat4& T);
	constexpr static mat4 Identity() { return mat4{}; }

	static mat4 ZeroMatrix()
	{
		mat4 r;
		memset(r.cell, 0, 64);
		return r;
	}

	static mat4 RotateX(const float a)
	{
		mat4 r;
		r.cell[5] = cosf(a);
		r.cell[6] = -sinf(a);
		r.cell[9] = sinf(a);
		r.cell[10] = cosf(a);
		return r;
	};

	static mat4 RotateY(const float a)
	{
		mat4 r;
		r.cell[0] = cosf(a);
		r.cell[2] = sinf(a);
		r.cell[8] = -sinf(a);
		r.cell[10] = cosf(a);
		return r;
	};

	static mat4 RotateZ(const float a)
	{
		mat4 r;
		r.cell[0] = cosf(a);
		r.cell[1] = -sinf(a);
		r.cell[4] = sinf(a);
		r.cell[5] = cosf(a);
		return r;
	};

	static mat4 Scale(const float s)
	{
		mat4 r;
		r.cell[0] = r.cell[5] = r.cell[10] = s;
		return r;
	}

	static mat4 Scale(const float3 s)
	{
		mat4 r;
		r.cell[0] = s.x, r.cell[5] = s.y, r.cell[10] = s.z;
		return r;
	}

	static mat4 Scale(const float4 s)
	{
		mat4 r;
		r.cell[0] = s.x, r.cell[5] = s.y, r.cell[10] = s.z, r.cell[15] = s.w;
		return r;
	}

	static mat4 Rotate(const float3& u, const float a) { return Rotate(u.x, u.y, u.z, a); }
	static mat4 Rotate(const float x, const float y, const float z, const float a);

	static mat4 LookAt(const float3 P, const float3 T);

	static mat4 LookAt(const float3& pos, const float3& look, const float3& up);

	static mat4 Translate(const float x, const float y, const float z)
	{
		mat4 r;
		r.cell[3] = x;
		r.cell[7] = y;
		r.cell[11] = z;
		return r;
	};

	static mat4 Translate(const float3 P)
	{
		mat4 r;
		r.cell[3] = P.x;
		r.cell[7] = P.y;
		r.cell[11] = P.z;
		return r;
	};
	float Trace3() const { return cell[0] + cell[5] + cell[10]; }
	[[nodiscard]] mat4 Transposed() const;
	[[nodiscard]] mat4 Inverted() const;
	[[nodiscard]] mat4 Inverted3x3() const;

	[[nodiscard]] float3 TransformVector(const float3& v) const;
	[[nodiscard]] float3 TransformPoint(const float3& v) const;
};

mat4 operator *(const mat4& a, const mat4& b);
mat4 operator +(const mat4& a, const mat4& b);
mat4 operator *(const mat4& a, const float s);
mat4 operator *(const float s, const mat4& a);
bool operator ==(const mat4& a, const mat4& b);
bool operator !=(const mat4& a, const mat4& b);
float4 operator *(const mat4& a, const float4& b);
float4 operator *(const float4& a, const mat4& b);

float3 TransformPosition(const float3& a, const mat4& M);
float3 TransformVector(const float3& a, const mat4& M);

class quat // based on https://github.com/adafruit
{
public:
	quat() = default;

	quat(float _w, float _x, float _y, float _z) : w(_w), x(_x), y(_y), z(_z)
	{
	}

	quat(float _w, float3 v) : w(_w), x(v.x), y(v.y), z(v.z)
	{
	}

	float magnitude() const { return sqrtf(w * w + x * x + y * y + z * z); }

	void normalize()
	{
		float m = magnitude();
		*this = this->scale(1 / m);
	}

	quat conjugate() const { return quat(w, -x, -y, -z); }
	void fromAxisAngle(const float3& axis, float theta);
	void fromMatrix(const mat4& m);
	void toAxisAngle(float3& axis, float& angle) const;

	mat4 toMatrix() const;
	float3 toEuler() const;
	float3 toAngularVelocity(float dt) const;

	float3 rotateVector(const float3& v) const;

	quat operator *(const quat& q) const;

	static quat slerp(const quat& a, const quat& b, const float t);
	quat operator +(const quat& q) const { return quat(w + q.w, x + q.x, y + q.y, z + q.z); }
	quat operator -(const quat& q) const { return quat(w - q.w, x - q.x, y - q.y, z - q.z); }
	quat operator /(float s) const { return quat(w / s, x / s, y / s, z / s); }
	quat operator *(float s) const { return scale(s); }
	quat scale(float s) const { return quat(w * s, x * s, y * s, z * s); }
	float w = 1, x = 0, y = 0, z = 0;
};
