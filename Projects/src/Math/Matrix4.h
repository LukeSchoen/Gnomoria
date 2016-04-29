#pragma once

#include "Vector.h"

class Matrix4
{
	Matrix4();
	Matrix4(float m00, float m01, float m02, float m03,
			float m10, float m11, float m12, float m13,
			float m20, float m21, float m22, float m23,
			float m30, float m31, float m32, float m33);

	void LoadIdentity();
	void Zero();
	void Ortho(float left, float right, float bottom, float top, float near, float far);
	void Ortho(float left, float right, float bottom, float top);
	void Perspective(float FOV, float aspectRatio, float near, float far);

	void Translate(float x, float y, float z);
	void Translate(const Vec3 &vec);
	void Scale(float x, float y, float z);
	void Scale(float num);
	void Rotate(float x, float y, float z);
	void RotateDegrees(float x, float y, float z);
	//void Rotate(Quaternion q);
	void RotateX(float radians);
	void RotateY(float radians);
	void RotateZ(float radians);

	float determinant() const;
	Matrix4& inverse();

	float& Get(int i, int j);

	Matrix4 operator*(const Matrix4 &mat2) const;
	void operator*=(const Matrix4 &mat2);
	void operator=(const Matrix4 &mat2);

	float m[4][4];
};