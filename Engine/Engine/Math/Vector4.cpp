#include "Vector4.h"

Vector4::Vector4():px(0.0f), py(0.0f),pz(0.0f),pw(0.0f)
{	
}

Vector4::Vector4(float i_x, float i_y, float i_z, float i_w) : px(i_x), py(i_y), pz(i_z), pw(i_w)
{
}

Vector4 Vector4::operator=(const Vector4 & v)
{
	if (this != &v) {
		px = v.X();
		py = v.Y();
		pz = v.Z();
		pw = v.W();
	}
	return *this;
}

const Vector4 Vector4::operator*(const float & scalar) const
{
	return Vector4(px*scalar, py*scalar, pz*scalar, pw*scalar);
}

const Vector4 Vector4::operator+(const Vector4 & v) const
{
	return Vector4
	(	px + v.X(),
		py + v.Y(),
		pz + v.Z(),
		pw + v.W()
	);
}

const Vector4 Vector4::Scale(const Vector4 & A, const Vector4 & B) const
{
	return Vector4();
}

std::ostream & operator<<(std::ostream & os, const Vector4 & v4)
{
	os << "(" << v4.X() << "," << v4.Y() << "," << v4.Z() << "," << v4.W() << ")";
	return os;
}
