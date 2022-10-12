#include "precomp.h"
#include "template_math.h"

using namespace Tmpl8;

mat4& mat4::operator+=(const mat4& a)
{
	for (int i = 0; i < 16; i++) cell[i] += a.cell[i];
	return *this;
}

float3 mat4::GetTranslation() const
{ return float3(cell[3], cell[7], cell[11]); }

mat4 mat4::FromColumnMajor(const mat4& T)
{
	mat4 M;
	M.cell[0] = T.cell[0], M.cell[1] = T.cell[4], M.cell[2] = T.cell[8], M.cell[3] = T.cell[12];
	M.cell[4] = T.cell[1], M.cell[5] = T.cell[5], M.cell[6] = T.cell[9], M.cell[7] = T.cell[13];
	M.cell[8] = T.cell[2], M.cell[9] = T.cell[6], M.cell[10] = T.cell[10], M.cell[11] = T.cell[14];
	M.cell[12] = T.cell[3], M.cell[13] = T.cell[7], M.cell[14] = T.cell[11], M.cell[15] = T.cell[15];
	return M;
}

mat4 mat4::Rotate(const float x, const float y, const float z, const float a)
{
	const float c = cosf(a), l_c = 1 - c, s = sinf(a);
	// row major
	mat4 m;
	m[0] = x * x + (1 - x * x) * c, m[1] = x * y * l_c + z * s, m[2] = x * z * l_c - y * s, m[3] = 0;
	m[4] = x * y * l_c - z * s, m[5] = y * y + (1 - y * y) * c, m[6] = y * z * l_c + x * s, m[7] = 0;
	m[8] = x * z * l_c + y * s, m[9] = y * z * l_c - x * s, m[10] = z * z + (1 - z * z) * c, m[11] = 0;
	m[12] = m[13] = m[14] = 0, m[15] = 1;
	return m;
}

mat4 mat4::LookAt(const float3 P, const float3 T)
{
	const float3 z = normalize(T - P);
	const float3 x = normalize(cross(z, float3(0, 1, 0)));
	const float3 y = cross(x, z);
	mat4 M = Translate(P);
	M[0] = x.x, M[4] = x.y, M[8] = x.z;
	M[1] = y.x, M[5] = y.y, M[9] = y.z;
	M[2] = z.x, M[6] = z.y, M[10] = z.z;
	return M;
}

mat4 mat4::LookAt(const float3& pos, const float3& look, const float3& up)
{
	// PBRT's lookat
	mat4 cameraToWorld;
	// initialize fourth column of viewing matrix
	cameraToWorld(0, 3) = pos.x;
	cameraToWorld(1, 3) = pos.y;
	cameraToWorld(2, 3) = pos.z;
	cameraToWorld(3, 3) = 1;

	// initialize first three columns of viewing matrix
	float3 dir = normalize(look - pos);
	float3 right = cross(normalize(up), dir);
	if (dot(right, right) == 0)
	{
		printf(
			"\"up\" vector (%f, %f, %f) and viewing direction (%f, %f, %f) "
			"passed to LookAt are pointing in the same direction.  Using "
			"the identity transformation.\n",
			up.x, up.y, up.z, dir.x, dir.y, dir.z);
		return mat4();
	}
	right = normalize(right);
	float3 newUp = cross(dir, right);
	cameraToWorld(0, 0) = right.x, cameraToWorld(1, 0) = right.y;
	cameraToWorld(2, 0) = right.z, cameraToWorld(3, 0) = 0.;
	cameraToWorld(0, 1) = newUp.x, cameraToWorld(1, 1) = newUp.y;
	cameraToWorld(2, 1) = newUp.z, cameraToWorld(3, 1) = 0.;
	cameraToWorld(0, 2) = dir.x, cameraToWorld(1, 2) = dir.y;
	cameraToWorld(2, 2) = dir.z, cameraToWorld(3, 2) = 0.;
	return cameraToWorld.Inverted();
}

mat4 mat4::Transposed() const
{
	mat4 M;
	M[0] = cell[0], M[1] = cell[4], M[2] = cell[8];
	M[4] = cell[1], M[5] = cell[5], M[6] = cell[9];
	M[8] = cell[2], M[9] = cell[6], M[10] = cell[10];
	return M;
}

mat4 mat4::Inverted() const
{
	// from MESA, via http://stackoverflow.com/questions/1148309/inverting-a-4x4-matrix
	const float inv[16] = {
		cell[5] * cell[10] * cell[15] - cell[5] * cell[11] * cell[14] - cell[9] * cell[6] * cell[15] +
		cell[9] * cell[7] * cell[14] + cell[13] * cell[6] * cell[11] - cell[13] * cell[7] * cell[10],
		-cell[1] * cell[10] * cell[15] + cell[1] * cell[11] * cell[14] + cell[9] * cell[2] * cell[15] -
		cell[9] * cell[3] * cell[14] - cell[13] * cell[2] * cell[11] + cell[13] * cell[3] * cell[10],
		cell[1] * cell[6] * cell[15] - cell[1] * cell[7] * cell[14] - cell[5] * cell[2] * cell[15] +
		cell[5] * cell[3] * cell[14] + cell[13] * cell[2] * cell[7] - cell[13] * cell[3] * cell[6],
		-cell[1] * cell[6] * cell[11] + cell[1] * cell[7] * cell[10] + cell[5] * cell[2] * cell[11] -
		cell[5] * cell[3] * cell[10] - cell[9] * cell[2] * cell[7] + cell[9] * cell[3] * cell[6],
		-cell[4] * cell[10] * cell[15] + cell[4] * cell[11] * cell[14] + cell[8] * cell[6] * cell[15] -
		cell[8] * cell[7] * cell[14] - cell[12] * cell[6] * cell[11] + cell[12] * cell[7] * cell[10],
		cell[0] * cell[10] * cell[15] - cell[0] * cell[11] * cell[14] - cell[8] * cell[2] * cell[15] +
		cell[8] * cell[3] * cell[14] + cell[12] * cell[2] * cell[11] - cell[12] * cell[3] * cell[10],
		-cell[0] * cell[6] * cell[15] + cell[0] * cell[7] * cell[14] + cell[4] * cell[2] * cell[15] -
		cell[4] * cell[3] * cell[14] - cell[12] * cell[2] * cell[7] + cell[12] * cell[3] * cell[6],
		cell[0] * cell[6] * cell[11] - cell[0] * cell[7] * cell[10] - cell[4] * cell[2] * cell[11] +
		cell[4] * cell[3] * cell[10] + cell[8] * cell[2] * cell[7] - cell[8] * cell[3] * cell[6],
		cell[4] * cell[9] * cell[15] - cell[4] * cell[11] * cell[13] - cell[8] * cell[5] * cell[15] +
		cell[8] * cell[7] * cell[13] + cell[12] * cell[5] * cell[11] - cell[12] * cell[7] * cell[9],
		-cell[0] * cell[9] * cell[15] + cell[0] * cell[11] * cell[13] + cell[8] * cell[1] * cell[15] -
		cell[8] * cell[3] * cell[13] - cell[12] * cell[1] * cell[11] + cell[12] * cell[3] * cell[9],
		cell[0] * cell[5] * cell[15] - cell[0] * cell[7] * cell[13] - cell[4] * cell[1] * cell[15] +
		cell[4] * cell[3] * cell[13] + cell[12] * cell[1] * cell[7] - cell[12] * cell[3] * cell[5],
		-cell[0] * cell[5] * cell[11] + cell[0] * cell[7] * cell[9] + cell[4] * cell[1] * cell[11] -
		cell[4] * cell[3] * cell[9] - cell[8] * cell[1] * cell[7] + cell[8] * cell[3] * cell[5],
		-cell[4] * cell[9] * cell[14] + cell[4] * cell[10] * cell[13] + cell[8] * cell[5] * cell[14] -
		cell[8] * cell[6] * cell[13] - cell[12] * cell[5] * cell[10] + cell[12] * cell[6] * cell[9],
		cell[0] * cell[9] * cell[14] - cell[0] * cell[10] * cell[13] - cell[8] * cell[1] * cell[14] +
		cell[8] * cell[2] * cell[13] + cell[12] * cell[1] * cell[10] - cell[12] * cell[2] * cell[9],
		-cell[0] * cell[5] * cell[14] + cell[0] * cell[6] * cell[13] + cell[4] * cell[1] * cell[14] -
		cell[4] * cell[2] * cell[13] - cell[12] * cell[1] * cell[6] + cell[12] * cell[2] * cell[5],
		cell[0] * cell[5] * cell[10] - cell[0] * cell[6] * cell[9] - cell[4] * cell[1] * cell[10] +
		cell[4] * cell[2] * cell[9] + cell[8] * cell[1] * cell[6] - cell[8] * cell[2] * cell[5]
	};
	const float det = cell[0] * inv[0] + cell[1] * inv[4] + cell[2] * inv[8] + cell[3] * inv[12];
	mat4 retVal;
	if (det != 0)
	{
		const float invdet = 1.0f / det;
		for (int i = 0; i < 16; i++) retVal.cell[i] = inv[i] * invdet;
	}
	return retVal;
}

mat4 mat4::Inverted3x3() const
{
	// via https://stackoverflow.com/questions/983999/simple-3x3-matrix-inverse-code-c
	const float invdet = 1.0f / (cell[0] * (cell[5] * cell[10] - cell[6] * cell[9]) -
		cell[4] * (cell[1] * cell[10] - cell[9] * cell[2]) +
		cell[8] * (cell[1] * cell[6] - cell[5] * cell[2]));
	mat4 R;
	R.cell[0] = (cell[5] * cell[10] - cell[6] * cell[9]) * invdet;
	R.cell[4] = (cell[8] * cell[6] - cell[4] * cell[10]) * invdet;
	R.cell[8] = (cell[4] * cell[9] - cell[8] * cell[5]) * invdet;
	R.cell[1] = (cell[9] * cell[2] - cell[1] * cell[10]) * invdet;
	R.cell[5] = (cell[0] * cell[10] - cell[8] * cell[2]) * invdet;
	R.cell[9] = (cell[1] * cell[8] - cell[0] * cell[9]) * invdet;
	R.cell[2] = (cell[1] * cell[6] - cell[2] * cell[5]) * invdet;
	R.cell[6] = (cell[2] * cell[4] - cell[0] * cell[6]) * invdet;
	R.cell[10] = (cell[0] * cell[5] - cell[1] * cell[4]) * invdet;
	return R;
}

float3 mat4::TransformVector(const float3& v) const
{
	return float3(cell[0] * v.x + cell[1] * v.y + cell[2] * v.z,
		cell[4] * v.x + cell[5] * v.y + cell[6] * v.z,
		cell[8] * v.x + cell[9] * v.y + cell[10] * v.z);
}

float3 mat4::TransformPoint(const float3& v) const
{
	const float3 res = float3(
		cell[0] * v.x + cell[1] * v.y + cell[2] * v.z + cell[3],
		cell[4] * v.x + cell[5] * v.y + cell[6] * v.z + cell[7],
		cell[8] * v.x + cell[9] * v.y + cell[10] * v.z + cell[11]);
	const float w = cell[12] * v.x + cell[13] * v.y + cell[14] * v.z + cell[15];
	if (w == 1) return res;
	return res * (1.f / w);
}

mat4 operator*(const mat4& a, const mat4& b)
{
	mat4 r;
	for (uint i = 0; i < 16; i += 4)
		for (uint j = 0; j < 4; ++j)
		{
			r[i + j] =
				(a.cell[i + 0] * b.cell[j + 0]) +
				(a.cell[i + 1] * b.cell[j + 4]) +
				(a.cell[i + 2] * b.cell[j + 8]) +
				(a.cell[i + 3] * b.cell[j + 12]);
		}
	return r;
}

mat4 operator*(const mat4& a, const float s)
{
	mat4 r;
	for (uint i = 0; i < 16; i += 4) r.cell[i] = a.cell[i] * s;
	return r;
}

mat4 operator*(const float s, const mat4& a)
{
	mat4 r;
	for (uint i = 0; i < 16; i++) r.cell[i] = a.cell[i] * s;
	return r;
}

mat4 operator+(const mat4& a, const mat4& b)
{
	mat4 r;
	for (uint i = 0; i < 16; i += 4) r.cell[i] = a.cell[i] + b.cell[i];
	return r;
}
bool operator==(const mat4& a, const mat4& b)
{
	for (uint i = 0; i < 16; i++)
		if (a.cell[i] != b.cell[i]) return false;
	return true;
}
bool operator!=(const mat4& a, const mat4& b) { return !(a == b); }
float4 operator*(const mat4& a, const float4& b)
{
	return float4(a.cell[0] * b.x + a.cell[1] * b.y + a.cell[2] * b.z + a.cell[3] * b.w,
		a.cell[4] * b.x + a.cell[5] * b.y + a.cell[6] * b.z + a.cell[7] * b.w,
		a.cell[8] * b.x + a.cell[9] * b.y + a.cell[10] * b.z + a.cell[11] * b.w,
		a.cell[12] * b.x + a.cell[13] * b.y + a.cell[14] * b.z + a.cell[15] * b.w);
}
float4 operator*(const float4& a, const mat4& b)
{
	return float4(b.cell[0] * a.x + b.cell[1] * a.y + b.cell[2] * a.z + b.cell[3] * a.w,
		b.cell[4] * a.x + b.cell[5] * a.y + b.cell[6] * a.z + b.cell[7] * a.w,
		b.cell[8] * a.x + b.cell[9] * a.y + b.cell[10] * a.z + b.cell[11] * a.w,
		b.cell[12] * a.x + b.cell[13] * a.y + b.cell[14] * a.z + b.cell[15] * a.w);
}
float3 TransformPosition(const float3& a, const mat4& M)
{
	return (float4(a, 1) * M).xyz;
}
float3 TransformVector(const float3& a, const mat4& M)
{
	return (float4(a, 0) * M).xyz;
}

void quat::fromAxisAngle(const float3& axis, float theta)
{
	w = cosf(theta / 2);
	const float s = sinf(theta / 2);
	x = axis.x * s, y = axis.y * s, z = axis.z * s;
}

void quat::fromMatrix(const mat4& m)
{
	float tr = m.Trace3(), S;
	if (tr > 0)
	{
		S = sqrtf(tr + 1.0f) * 2, w = 0.25f * S;
		x = (m(2, 1) - m(1, 2)) / S, y = (m(0, 2) - m(2, 0)) / S;
		z = (m(1, 0) - m(0, 1)) / S;
	}
	else if (m(0, 0) > m(1, 1) && m(0, 0) > m(2, 2))
	{
		S = sqrt(1.0f + m(0, 0) - m(1, 1) - m(2, 2)) * 2;
		w = (m(2, 1) - m(1, 2)) / S, x = 0.25f * S;
		y = (m(0, 1) + m(1, 0)) / S, z = (m(0, 2) + m(2, 0)) / S;
	}
	else if (m(1, 1) > m(2, 2))
	{
		S = sqrt(1.0f + m(1, 1) - m(0, 0) - m(2, 2)) * 2;
		w = (m(0, 2) - m(2, 0)) / S;
		x = (m(0, 1) + m(1, 0)) / S, y = 0.25f * S;
		z = (m(1, 2) + m(2, 1)) / S;
	}
	else
	{
		S = sqrt(1.0f + m(2, 2) - m(0, 0) - m(1, 1)) * 2;
		w = (m(1, 0) - m(0, 1)) / S, x = (m(0, 2) + m(2, 0)) / S;
		y = (m(1, 2) + m(2, 1)) / S, z = 0.25f * S;
	}
}

void quat::toAxisAngle(float3& axis, float& angle) const
{
	float s = sqrtf(1 - w * w);
	if (s == 0) return;
	angle = 2 * acosf(w);
	axis.x = x / s, axis.y = y / s, axis.z = z / s;
}

mat4 quat::toMatrix() const
{
	mat4 ret;
	ret.cell[0] = 1 - 2 * y * y - 2 * z * z;
	ret.cell[1] = 2 * x * y - 2 * w * z, ret.cell[2] = 2 * x * z + 2 * w * y, ret.cell[4] = 2 * x * y + 2 * w * z;
	ret.cell[5] = 1 - 2 * x * x - 2 * z * z;
	ret.cell[6] = 2 * y * z - 2 * w * x, ret.cell[8] = 2 * x * z - 2 * w * y, ret.cell[9] = 2 * y * z + 2 * w * x;
	ret.cell[10] = 1 - 2 * x * x - 2 * y * y;
	return ret;
}

float3 quat::toEuler() const
{
	float3 ret;
	float sqw = w * w, sqx = x * x, sqy = y * y, sqz = z * z;
	ret.x = atan2f(2.0f * (x * y + z * w), (sqx - sqy - sqz + sqw));
	ret.y = asinf(-2.0f * (x * z - y * w) / (sqx + sqy + sqz + sqw));
	ret.z = atan2f(2.0f * (y * z + x * w), (-sqx - sqy + sqz + sqw));
	return ret;
}

float3 quat::toAngularVelocity(float dt) const
{
	float3 ret;
	quat one(1, 0, 0, 0), delta = one - *this, r = (delta / dt);
	r = r * 2, r = r * one, ret.x = r.x, ret.y = r.y, ret.z = r.z;
	return ret;
}

float3 quat::rotateVector(const float3& v) const
{
	float3 qv = float3(x, y, z), t = cross(qv, v) * 2.0f;
	return v + t * w + cross(qv, t);
}

quat quat::operator*(const quat& q) const
{
	return quat(
		w * q.w - x * q.x - y * q.y - z * q.z, w * q.x + x * q.w + y * q.z - z * q.y,
		w * q.y - x * q.z + y * q.w + z * q.x, w * q.z + x * q.y - y * q.x + z * q.w
	);
}

quat quat::slerp(const quat& a, const quat& b, const float t)
{
	// from https://www.euclideanspace.com/maths/algebra/realNormedAlgebra/quaternions/slerp/index.htm
	quat qm;
	float cosHalfTheta = a.w * b.w + a.x * b.x + a.y * b.y + a.z * b.z;
	if (std::abs(cosHalfTheta) >= 1.0)
	{
		qm.w = a.w, qm.x = a.x, qm.y = a.y, qm.z = a.z;
		return qm;
	}
	float halfTheta = acosf(cosHalfTheta);
	float sinHalfTheta = sqrtf(1.0f - cosHalfTheta * cosHalfTheta);
	if (std::fabs(sinHalfTheta) < 0.001f)
	{
		qm.w = a.w * 0.5f + b.w * 0.5f, qm.x = a.x * 0.5f + b.x * 0.5f;
		qm.y = a.y * 0.5f + b.y * 0.5f, qm.z = a.z * 0.5f + b.z * 0.5f;
		return qm;
	}
	float ratioA = sinf((1 - t) * halfTheta) / sinHalfTheta;
	float ratioB = sinf(t * halfTheta) / sinHalfTheta;
	qm.w = (a.w * ratioA + b.w * ratioB), qm.x = (a.x * ratioA + b.x * ratioB);
	qm.y = (a.y * ratioA + b.y * ratioB), qm.z = (a.z * ratioA + b.z * ratioB);
	return qm;
}
