#define _USE_MATH_DEFINES
#include "Matrix4.h"
#include <cmath>
#include "Math/Floats.h"
Matrix4::Matrix4()
{
	(*this) = Identity();
}

Matrix4::Matrix4(float i_11, float i_12, float i_13, float i_14, float i_21, float i_22, float i_23, float i_24, float i_31, float i_32, float i_33, float i_34, float i_41, float i_42, float i_43, float i_44)
{
	m[0][0] = i_11;
	m[0][1] = i_12;
	m[0][2] = i_13;
	m[0][3] = i_14;

	m[1][0] = i_21;
	m[1][1] = i_22;
	m[1][2] = i_23;
	m[1][3] = i_24;

	m[2][0] = i_31;
	m[2][1] = i_32;
	m[2][2] = i_33;
	m[2][3] = i_34;

	m[3][0] = i_41;
	m[3][1] = i_42;
	m[3][2] = i_43;
	m[3][3] = i_44;
}

Matrix4::Matrix4(const Vector4 & v1, const Vector4 & v2, const Vector4 & v3, const Vector4 & v4)
{
	m[0][0] = v1.X();
	m[0][1] = v1.Y();
	m[0][2] = v1.Z();
	m[0][3] = v1.W();

	m[1][0] = v2.X();
	m[1][1] = v2.Y();
	m[1][2] = v2.Z();
	m[1][3] = v2.W();

	m[2][0] = v3.X();
	m[2][1] = v3.Y();
	m[2][2] = v3.Z();
	m[2][3] = v3.W();

	m[3][0] = v4.X();
	m[3][1] = v4.Y();
	m[3][2] = v4.Z();
	m[3][3] = v4.W();
}

const bool Matrix4::operator==(const Matrix4 & M) const
{
	for (unsigned int row = 0; row < 4; row++)
	{
		for (unsigned int col = 0; col < 4; col++)
		{
			
			if (!(Floats::RelativeEpsilonEqual(m[row][col], M(row, col), .000001f)))
			{
				return false;
			}
		}
	}
	return true;
}

Matrix4 & Matrix4::operator=(const Matrix4 & i_M)
{
	for (unsigned int row = 0; row < 4; row++)
	{
		for (unsigned int col = 0; col < 4; col++)
		{
			m[row][col] = i_M(row,col);
		}
	}
	return (*this);
}

float& Matrix4::operator() (unsigned row, unsigned col)
{
	return m[row][col];
}

float Matrix4::operator()(unsigned int row, unsigned int col) const
{
	return m[row][col];
}

Vector4 Matrix4::operator()(unsigned col) const
{
	return Vector4(m[0][col],m[1][col],m[2][col], m[3][col]);
}

Matrix4 Matrix4::createTranslation(float x, float y, float z)
{
	return Matrix4
	(
		1,0,0,x,
		0,1,0,y,
		0,0,1,z,
		0,0,0,1.0f
	);
}

Matrix4 Matrix4::createScale(float x, float y, float z)
{
	return Matrix4
	(
		x, 0, 0, 0,
		0, y, 0, 0,
		0, 0, z, 0,
		0, 0, 0, 1.0f
	);
}

Matrix4 Matrix4::createRotationX(float theta)
{
	theta = theta * (float)(M_PI/180);
	return Matrix4
	(
		1.0f,	0,			0,		0,
		0, cos(theta), -sin(theta),	0,
		0, sin(theta), cos(theta), 0,
		0,		0,			0,		1.0f
	);
}

Matrix4 Matrix4::createRotationY(float theta)
{
	theta = theta * (float)(M_PI / 180);
	return Matrix4
	(
		cos(theta), 0,sin(theta),	0,
		0,			1.0f,	0,			0,
		-sin(theta), 0,	cos(theta),		0,
		0,			0,		0,			1.0f
	);
}

Matrix4 Matrix4::createRotationZ(float theta)
{
	theta = theta * (float)(M_PI / 180);
	return Matrix4
	(
		cos(theta), -sin(theta),0,		0,
		sin(theta), cos(theta), 0,		0,
		0,				0,		1.0f,	0,
		0,				0,		0,		1.0f
	);
}

Matrix4 Matrix4::Identity()
{
	return Matrix4
	(
		1.0f, 0, 0, 0,
		0, 1.0f, 0, 0,
		0, 0, 1.0f, 0,
		0, 0, 0, 1.0f
	);
}

//Computes the transpose of the matrix.
//if forInverseTransform is true the returned matrix will be of a form for reversing transformations
Matrix4 Matrix4::getTranspose(bool forInverseTransform)
{
	Matrix4 rTrans;
	for (unsigned int i = 0; i < 4; i++)
	{
		for (unsigned int j = 0; j < 4; j++)
		{
			rTrans(j, i) = m[i][j];
		}
	}

	Matrix4 translation;
	if (forInverseTransform)
	{
		rTrans(0, 3) = 0;
		rTrans(1, 3) = 0;
		rTrans(2, 3) = 0;

		rTrans(3, 0) = 0;
		rTrans(3, 1) = 0;
		rTrans(3, 2) = 0;

		rTrans(3, 3) = 1;

		
		translation(0, 3) = -m[0][3];
		translation(1, 3) = -m[1][3];
		translation(2, 3) = -m[2][3];
	}
	return (rTrans*translation);
}

std::ostream & operator<<(std::ostream & os, const Matrix4 & m4)
{
	for (unsigned int row = 0; row < 4; row++)
	{
		for (unsigned int col = 0; col < 4; col++)
		{
			os << m4(row, col) << ",";
		}
		os << "\n";
	}
	return os;
}

// Allows us to use V = M * V (i.e. column vector)
Vector4 operator*(const Matrix4 & i_mtx, const Vector4 & i_vec)
{
	float result[4];

	for (int i = 0; i < 4; ++i)
	{
		float sum = 0;
		for (int j = 0; j < 4; ++j)
		{
			sum += i_mtx(i, j)*i_vec(j);
		}
		result[i] = sum;
	}
	Vector4 resultVec(result);	
	return resultVec;
}

const Matrix4 operator*(const Matrix4 & RHS, const Matrix4 & LHS)
{
	Matrix4 result;
	for (unsigned int row = 0; row < 4; row++)
	{
		for (unsigned int col = 0; col < 4; col++)
		{
			float sum = 0;
			for (unsigned int i = 0; i < 4; i++)
			{
				sum += RHS(row, i)*LHS(i, col);
			}
			result(row, col) = sum;
		}
	}
	return result;
}
