#include "Matrix4.h"

Matrix4::Matrix4()
{
}

Matrix4::Matrix4(float i_11, float i_12, float i_13, float i_14, float i_21, float i_22, float i_23, float i_24, float i_31, float i_32, float i_33, float i_34, float i_41, float i_42, float i_43, float i_44)
{
}

Matrix4::Matrix4(const Vector4 & v1, const Vector4 & v2, const Vector4 & v3, const Vector4 & v4)
{
}

float Matrix4::operator()(unsigned row, unsigned col) const
{
	return 0.0f;
}

Matrix4 Matrix4::createTranslation(float x, float y, float z)
{
	return Matrix4();
}

Matrix4 Matrix4::createScale(float x, float y, float z)
{
	return Matrix4();
}

Matrix4 Matrix4::createRotationX(float angle)
{
	return Matrix4();
}

Matrix4 Matrix4::createRotationY(float angle)
{
	return Matrix4();
}

Matrix4 Matrix4::createRotationZ(float angle)
{
	return Matrix4();
}

Matrix4 Matrix4::getTranspose()
{
	return Matrix4();
}

// Allows us to use V = M * V (i.e. column vector)
inline Vector4 operator*(const Matrix4 & i_mtx, const Vector4 & i_vec)
{
	return Vector4();
}
// Allows us to use V = V * M; (i.e. row vector)
inline Vector4 operator*(const Vector4 & i_vec, const Matrix4 & i_mtx)
{
	return Vector4();
}

const Matrix4 operator*(const Matrix4 & RHS, const Matrix4 & LHS)
{
	return Matrix4();
}
