#include "Vector4.h"
#include "../Floats.h"

Vector4::Vector4():px(0.0f), py(0.0f),pz(0.0f),pw(0.0f)
{	
}

Vector4::Vector4(float i_x, float i_y, float i_z, float i_w) : px(i_x), py(i_y), pz(i_z), pw(i_w)
{
}

Vector4::Vector4(float values[4]):px(values[0]), py(values[1]), pz(values[2]), pw(values[3])
{
}

Vector4::Vector4(const Vector4 & v4)
{
	px = v4.X();
	py = v4.Y();
	pz = v4.Z();
	pw = v4.W();
}

const bool Vector4::operator==(const Vector4 & v4) const
{	
	bool X = Floats::RelativeEpsilonEqual(px, v4.X(),.000001);
	bool Y = Floats::RelativeEpsilonEqual(py, v4.Y(), .000001);
	bool Z = Floats::RelativeEpsilonEqual(pz, v4.Z(), .000001);
	bool W = Floats::RelativeEpsilonEqual(pw, v4.W(), .000001);

	return (X && Y && Z && W);
		
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

const float Vector4::operator()(int index) const
{
	switch (index)
	{
	case 0:
		return px;
		break;
	case 1:
		return py;
		break;
	case 2:
		return pz;
		break;
	case 3:
		return pw;
		break;
	default:
		return INFINITY;
	}
}

std::ostream & operator<<(std::ostream & os, const Vector4 & v4)
{
	os << "(" << v4.X() << "," << v4.Y() << "," << v4.Z() << "," << v4.W() << ")";
	return os;
}
