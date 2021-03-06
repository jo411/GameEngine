#pragma once
#include "Vector4.h"
class Matrix4
{
public:
	Matrix4();
	Matrix4(float i_11, float i_12, float i_13, float i_14,
			float i_21, float i_22, float i_23, float i_24,
			float i_31, float i_32, float i_33, float i_34,
			float i_41, float i_42, float i_43, float i_44);

	Matrix4(const Vector4& v1, const Vector4& v2, const Vector4& v3, const Vector4& v4);

	const bool operator ==(const Matrix4& M) const;
	Matrix4& operator = (const Matrix4 &M);
	
	float&	operator() (unsigned row, unsigned col);
	float	operator() (unsigned int row, unsigned int col)  const;
	Vector4 operator() (unsigned col) const;

	static Matrix4 createTranslation(float x, float y, float z);
	static Matrix4 createScale(float x, float y, float z);
	static Matrix4 createRotationX(float theta);
	static Matrix4 createRotationY(float theta);
	static Matrix4 createRotationZ(float theta);
	static Matrix4 Identity();
		
	Matrix4 getTranspose(bool forInverseTransform);


	friend std::ostream& operator<<(std::ostream& os, const Matrix4& m4);
private:

	float m[4][4];
	
};
// Allows us to use V = M * V (i.e. column vector)
Vector4 operator*(const Matrix4& i_mtx, const Vector4& i_vec);

const Matrix4 operator* (const Matrix4 &RHS, const Matrix4 &LHS);

