#include "Matrix4.h"

#include "MathUtil.h"
#include <string.h>	// memset

Matrix4::Matrix4()
{}

Matrix4::Matrix4(float m00, float m01, float m02, float m03,
	float m10, float m11, float m12, float m13,
	float m20, float m21, float m22, float m23,
	float m30, float m31, float m32, float m33)
{
	m[0][0] = m00; m[0][1] = m01; m[0][2] = m02; m[0][3] = m03;
	m[1][0] = m10; m[1][1] = m11; m[1][2] = m12; m[1][3] = m13;
	m[2][0] = m20; m[2][1] = m21; m[2][2] = m22; m[2][3] = m23;
	m[3][0] = m30; m[3][1] = m31; m[3][2] = m32; m[3][3] = m33;
}

void Matrix4::LoadIdentity()
{
	m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = 0.0f;
	m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f; m[1][3] = 0.0f;
	m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f; m[2][3] = 0.0f;
	m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;
}

void Matrix4::Zero()
{
	memset(m, 0, sizeof(m));
}

void Matrix4::Ortho(float left, float right, float bottom, float top, float near, float far)
{
	m[0][0] = 2.0f / (right - left);
	m[0][1] = 0.0f;
	m[0][2] = 0.0f;
	m[0][3] = 0.0f;

	m[1][0] = 0.0f;
	m[1][1] = 2.0f / (top - bottom);
	m[1][2] = 0.0f;
	m[1][3] = 0.0f;

	m[2][0] = 0.0f;
	m[2][1] = 0.0f;
	m[2][2] = -2.0f / (far - near);
	m[2][3] = 0.0f;

	m[3][0] = -(right + left) / (right - left);
	m[3][1] = -(top + bottom) / (top - bottom);
	m[3][2] = -(far + near) / (far - near);
	m[3][3] = 1.0f;
}

void Matrix4::Ortho(float left, float right, float bottom, float top)
{
	m[0][0] = 2.0f / (right - left);
	m[0][1] = 0.0f;
	m[0][2] = 0.0f;
	m[0][3] = 0.0f;

	m[1][0] = 0.0f;
	m[1][1] = 2.0f / (top - bottom);
	m[1][2] = 0.0f;
	m[1][3] = 0.0f;

	m[2][0] = 0.0f;
	m[2][1] = 0.0f;
	m[2][2] = -1.0f;
	m[2][3] = 0.0f;

	m[3][0] = -(right + left) / (right - left);
	m[3][1] = -(top + bottom) / (top - bottom);
	m[3][2] = 0.0f;
	m[3][3] = 1.0f;
}

void Matrix4::Perspective(float FOV, float aspectRatio, float near, float far)
{
	static const float zRange = near - far;
	static const float tanHalfFOV = tanf(toRadian(FOV / 2.0f));

	m[0][0] = 1.0f / (tanHalfFOV * aspectRatio);
	m[0][1] = 0.0f;
	m[0][2] = 0.0f;
	m[0][3] = 0.0f;

	m[1][0] = 0.0f;
	m[1][1] = 1.0f / tanHalfFOV;
	m[1][2] = 0.0f;
	m[1][3] = 0.0f;

	m[2][0] = 0.0f;
	m[2][1] = 0.0f;
	m[2][2] = (-near - far) / zRange;
	m[2][3] = 2.0f * far * near / zRange;

	m[3][0] = 0.0f;
	m[3][1] = 0.0f;
	m[3][2] = 1.0f;
	m[3][3] = 0.0f;
}

void Matrix4::Translate(float x, float y, float z)
{
	Matrix4 mat2;

	mat2.m[0][0] = 1.0f; mat2.m[0][1] = 0.0f; mat2.m[0][2] = 0.0f; mat2.m[0][3] = x;
	mat2.m[1][0] = 0.0f; mat2.m[1][1] = 1.0f; mat2.m[1][2] = 0.0f; mat2.m[1][3] = y;
	mat2.m[2][0] = 0.0f; mat2.m[2][1] = 0.0f; mat2.m[2][2] = 1.0f; mat2.m[2][3] = z;
	mat2.m[3][0] = 0.0f; mat2.m[3][1] = 0.0f; mat2.m[3][2] = 0.0f; mat2.m[3][3] = 1.0f;

	*this *= mat2;
}

void Matrix4::Translate(const Vec3& vec)
{
	Matrix4 mat2;

	mat2.m[0][0] = 1.0f; mat2.m[0][1] = 0.0f; mat2.m[0][2] = 0.0f; mat2.m[0][3] = vec.x;
	mat2.m[1][0] = 0.0f; mat2.m[1][1] = 1.0f; mat2.m[1][2] = 0.0f; mat2.m[1][3] = vec.y;
	mat2.m[2][0] = 0.0f; mat2.m[2][1] = 0.0f; mat2.m[2][2] = 1.0f; mat2.m[2][3] = vec.z;
	mat2.m[3][0] = 0.0f; mat2.m[3][1] = 0.0f; mat2.m[3][2] = 0.0f; mat2.m[3][3] = 1.0f;

	*this *= mat2;
}

void Matrix4::Scale(float x, float y, float z)
{
	Matrix4 mat2;

	mat2.m[0][0] = x;	 mat2.m[0][1] = 0.0f; mat2.m[0][2] = 0.0f; mat2.m[0][3] = 0.0f;
	mat2.m[1][0] = 0.0f; mat2.m[1][1] = y;	mat2.m[1][2] = 0.0f; mat2.m[1][3] = 0.0f;
	mat2.m[2][0] = 0.0f; mat2.m[2][1] = 0.0f; mat2.m[2][2] = z;	mat2.m[2][3] = 0.0f;
	mat2.m[3][0] = 0.0f; mat2.m[3][1] = 0.0f; mat2.m[3][2] = 0.0f; mat2.m[3][3] = 1.0f;

	*this *= mat2;
}

void Matrix4::Scale(float num)
{
	Matrix4 mat2;

	mat2.m[0][0] = num;	mat2.m[0][1] = 0.0f; mat2.m[0][2] = 0.0f; mat2.m[0][3] = 0.0f;
	mat2.m[1][0] = 0.0f; mat2.m[1][1] = num;	mat2.m[1][2] = 0.0f; mat2.m[1][3] = 0.0f;
	mat2.m[2][0] = 0.0f; mat2.m[2][1] = 0.0f; mat2.m[2][2] = num;	mat2.m[2][3] = 0.0f;
	mat2.m[3][0] = 0.0f; mat2.m[3][1] = 0.0f; mat2.m[3][2] = 0.0f; mat2.m[3][3] = 1.0f;

	*this *= mat2;
}

void Matrix4::Rotate(float x, float y, float z)
{
	Matrix4 rx, ry, rz;

	float sinX = sinf(x);
	float cosX = cosf(x);
	float sinY = sinf(y);
	float cosY = cosf(y);
	float sinZ = sinf(z);
	float cosZ = cosf(z);
	
	rx.m[0][0] = 1.0f; rx.m[0][1] = 0.0f; rx.m[0][2] = 0.0f;  rx.m[0][3] = 0.0f;
	rx.m[1][0] = 0.0f; rx.m[1][1] = cosX; rx.m[1][2] = -sinX; rx.m[1][3] = 0.0f;
	rx.m[2][0] = 0.0f; rx.m[2][1] = sinX; rx.m[2][2] = cosX;  rx.m[2][3] = 0.0f;
	rx.m[3][0] = 0.0f; rx.m[3][1] = 0.0f; rx.m[3][2] = 0.0f;  rx.m[3][3] = 1.0f;

	ry.m[0][0] = cosY; ry.m[0][1] = 0.0f; ry.m[0][2] = -sinY; ry.m[0][3] = 0.0f;
	ry.m[1][0] = 0.0f; ry.m[1][1] = 1.0f; ry.m[1][2] = 0.0f; ry.m[1][3] = 0.0f;
	ry.m[2][0] = sinY; ry.m[2][1] = 0.0f; ry.m[2][2] = cosY; ry.m[2][3] = 0.0f;
	ry.m[3][0] = 0.0f; ry.m[3][1] = 0.0f; ry.m[3][2] = 0.0f; ry.m[3][3] = 1.0f;

	rz.m[0][0] = cosZ; rz.m[0][1] = -sinZ; rz.m[0][2] = 0.0f; rz.m[0][3] = 0.0f;
	rz.m[1][0] = sinZ; rz.m[1][1] = cosZ;  rz.m[1][2] = 0.0f; rz.m[1][3] = 0.0f;
	rz.m[2][0] = 0.0f; rz.m[2][1] = 0.0f;  rz.m[2][2] = 1.0f; rz.m[2][3] = 0.0f;
	rz.m[3][0] = 0.0f; rz.m[3][1] = 0.0f;  rz.m[3][2] = 0.0f; rz.m[3][3] = 1.0f;

	Matrix4 mat = rz * ry * rx;;

	*this *= mat;
}

void Matrix4::RotateDegrees(float x, float y, float z)
{
	Rotate(ToRadian(x), ToRadian(y), ToRadian(z));
}

void Matrix4::RotateX(float radians)
{
	Matrix4 r;

	float sinA = sinf(radians);
	float cosA = sinf(radians);

	r.m[0][0] = 1.0f; r.m[0][1] = 0.0f; r.m[0][2] = 0.0f;  r.m[0][3] = 0.0f;
	r.m[1][0] = 0.0f; r.m[1][1] = cosA; r.m[1][2] = -sinA; r.m[1][3] = 0.0f;
	r.m[2][0] = 0.0f; r.m[2][1] = sinA; r.m[2][2] = cosA;  r.m[2][3] = 0.0f;
	r.m[3][0] = 0.0f; r.m[3][1] = 0.0f; r.m[3][2] = 0.0f;  r.m[3][3] = 1.0f;
	
	*this *= r;
}

void Matrix4::RotateY(float radians)
{
	Matrix4 r;

	float sinA = sinf(radians);
	float cosA = sinf(radians);

	r.m[0][0] = cosA; r.m[0][1] = 0.0f; r.m[0][2] = -sinA; r.m[0][3] = 0.0f;
	r.m[1][0] = 0.0f; r.m[1][1] = 1.0f; r.m[1][2] = 0.0f;  r.m[1][3] = 0.0f;
	r.m[2][0] = sinA; r.m[2][1] = 0.0f; r.m[2][2] = cosA;  r.m[2][3] = 0.0f;
	r.m[3][0] = 0.0f; r.m[3][1] = 0.0f; r.m[3][2] = 0.0f;  r.m[3][3] = 1.0f;

	*this *= r;
}

void Matrix4::RotateZ(float radians)
{
	Matrix4 r;

	float sinA = sinf(radians);
	float cosA = sinf(radians);

	r.m[0][0] = cosA; r.m[0][1] = -sinA; r.m[0][2] = 0.0f; r.m[0][3] = 0.0f;
	r.m[1][0] = sinA; r.m[1][1] = cosA;	 r.m[1][2] = 0.0f; r.m[1][3] = 0.0f;
	r.m[2][0] = 0.0f; r.m[2][1] = 0.0f;	 r.m[2][2] = 1.0f; r.m[2][3] = 0.0f;
	r.m[3][0] = 0.0f; r.m[3][1] = 0.0f;	 r.m[3][2] = 0.0f; r.m[3][3] = 1.0f;

	*this *= r;
}

float Matrix4::determinant() const
{
	return m[0][0] * m[1][1] * m[2][2] * m[3][3] - m[0][0] * m[1][1] * m[2][3] * m[3][2] + m[0][0] * m[1][2] * m[2][3] * m[3][1] - m[0][0] * m[1][2] * m[2][1] * m[3][3] +
		   m[0][0] * m[1][3] * m[2][1] * m[3][2] - m[0][0] * m[1][3] * m[2][2] * m[3][1] - m[0][1] * m[1][2] * m[2][3] * m[3][0] + m[0][1] * m[1][2] * m[2][0] * m[3][3] -
		   m[0][1] * m[1][3] * m[2][0] * m[3][2] + m[0][1] * m[1][3] * m[2][2] * m[3][0] - m[0][1] * m[1][0] * m[2][2] * m[3][3] + m[0][1] * m[1][0] * m[2][3] * m[3][2] +
		   m[0][2] * m[1][3] * m[2][0] * m[3][1] - m[0][2] * m[1][3] * m[2][1] * m[3][0] + m[0][2] * m[1][0] * m[2][1] * m[3][3] - m[0][2] * m[1][0] * m[2][3] * m[3][1] +
		   m[0][2] * m[1][1] * m[2][3] * m[3][0] - m[0][2] * m[1][1] * m[2][0] * m[3][3] - m[0][3] * m[1][0] * m[2][1] * m[3][2] + m[0][3] * m[1][0] * m[2][2] * m[3][1] -
		   m[0][3] * m[1][1] * m[2][2] * m[3][0] + m[0][3] * m[1][1] * m[2][0] * m[3][2] - m[0][3] * m[1][2] * m[2][0] * m[3][1] + m[0][3] * m[1][2] * m[2][1] * m[3][0];
}

Matrix4& Matrix4::inverse()
{
	// Compute the reciprocal determinant
	float det = determinant();
	if (det == 0.0f)
	{
		assert(0);
		return *this;
	}

	float invdet = 1.0f / det;

	Matrix4 res;
	res.m[0][0] = invdet  * (m[1][1] * (m[2][2] * m[3][3] - m[2][3] * m[3][2]) + m[1][2] * (m[2][3] * m[3][1] - m[2][1] * m[3][3]) + m[1][3] * (m[2][1] * m[3][2] - m[2][2] * m[3][1]));
	res.m[0][1] = -invdet * (m[0][1] * (m[2][2] * m[3][3] - m[2][3] * m[3][2]) + m[0][2] * (m[2][3] * m[3][1] - m[2][1] * m[3][3]) + m[0][3] * (m[2][1] * m[3][2] - m[2][2] * m[3][1]));
	res.m[0][2] = invdet  * (m[0][1] * (m[1][2] * m[3][3] - m[1][3] * m[3][2]) + m[0][2] * (m[1][3] * m[3][1] - m[1][1] * m[3][3]) + m[0][3] * (m[1][1] * m[3][2] - m[1][2] * m[3][1]));
	res.m[0][3] = -invdet * (m[0][1] * (m[1][2] * m[2][3] - m[1][3] * m[2][2]) + m[0][2] * (m[1][3] * m[2][1] - m[1][1] * m[2][3]) + m[0][3] * (m[1][1] * m[2][2] - m[1][2] * m[2][1]));
	res.m[1][0] = -invdet * (m[1][0] * (m[2][2] * m[3][3] - m[2][3] * m[3][2]) + m[1][2] * (m[2][3] * m[3][0] - m[2][0] * m[3][3]) + m[1][3] * (m[2][0] * m[3][2] - m[2][2] * m[3][0]));
	res.m[1][1] = invdet  * (m[0][0] * (m[2][2] * m[3][3] - m[2][3] * m[3][2]) + m[0][2] * (m[2][3] * m[3][0] - m[2][0] * m[3][3]) + m[0][3] * (m[2][0] * m[3][2] - m[2][2] * m[3][0]));
	res.m[1][2] = -invdet * (m[0][0] * (m[1][2] * m[3][3] - m[1][3] * m[3][2]) + m[0][2] * (m[1][3] * m[3][0] - m[1][0] * m[3][3]) + m[0][3] * (m[1][0] * m[3][2] - m[1][2] * m[3][0]));
	res.m[1][3] = invdet  * (m[0][0] * (m[1][2] * m[2][3] - m[1][3] * m[2][2]) + m[0][2] * (m[1][3] * m[2][0] - m[1][0] * m[2][3]) + m[0][3] * (m[1][0] * m[2][2] - m[1][2] * m[2][0]));
	res.m[2][0] = invdet  * (m[1][0] * (m[2][1] * m[3][3] - m[2][3] * m[3][1]) + m[1][1] * (m[2][3] * m[3][0] - m[2][0] * m[3][3]) + m[1][3] * (m[2][0] * m[3][1] - m[2][1] * m[3][0]));
	res.m[2][1] = -invdet * (m[0][0] * (m[2][1] * m[3][3] - m[2][3] * m[3][1]) + m[0][1] * (m[2][3] * m[3][0] - m[2][0] * m[3][3]) + m[0][3] * (m[2][0] * m[3][1] - m[2][1] * m[3][0]));
	res.m[2][2] = invdet  * (m[0][0] * (m[1][1] * m[3][3] - m[1][3] * m[3][1]) + m[0][1] * (m[1][3] * m[3][0] - m[1][0] * m[3][3]) + m[0][3] * (m[1][0] * m[3][1] - m[1][1] * m[3][0]));
	res.m[2][3] = -invdet * (m[0][0] * (m[1][1] * m[2][3] - m[1][3] * m[2][1]) + m[0][1] * (m[1][3] * m[2][0] - m[1][0] * m[2][3]) + m[0][3] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]));
	res.m[3][0] = -invdet * (m[1][0] * (m[2][1] * m[3][2] - m[2][2] * m[3][1]) + m[1][1] * (m[2][2] * m[3][0] - m[2][0] * m[3][2]) + m[1][2] * (m[2][0] * m[3][1] - m[2][1] * m[3][0]));
	res.m[3][1] = invdet  * (m[0][0] * (m[2][1] * m[3][2] - m[2][2] * m[3][1]) + m[0][1] * (m[2][2] * m[3][0] - m[2][0] * m[3][2]) + m[0][2] * (m[2][0] * m[3][1] - m[2][1] * m[3][0]));
	res.m[3][2] = -invdet * (m[0][0] * (m[1][1] * m[3][2] - m[1][2] * m[3][1]) + m[0][1] * (m[1][2] * m[3][0] - m[1][0] * m[3][2]) + m[0][2] * (m[1][0] * m[3][1] - m[1][1] * m[3][0]));
	res.m[3][3] = invdet  * (m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1]) + m[0][1] * (m[1][2] * m[2][0] - m[1][0] * m[2][2]) + m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]));
	*this = res;

	return *this;
}

float& Matrix4::Get(int i, int j)
{
	return m[i][j];
}

Matrix4 Matrix4::operator*(const Matrix4& mat2) const
{
	Matrix4 Ret;

	for (unsigned int i = 0; i < 4; i++)
		for (unsigned int j = 0; j < 4; j++)
			Ret.m[i][j] = m[i][0] * mat2.m[0][j] +
						  m[i][1] * mat2.m[1][j] +
						  m[i][2] * mat2.m[2][j] +
						  m[i][3] * mat2.m[3][j];

	return Ret;
}

void Matrix4::operator*=(const Matrix4& mat2)
{
	*this = *this * mat2;
}

void Matrix4::operator=(const Matrix4& mat2)
{
	for (unsigned int i = 0; i < 4; i++)
		for (unsigned int j = 0; j < 4; j++)
			m[i][j] = mat2.m[i][j];
}