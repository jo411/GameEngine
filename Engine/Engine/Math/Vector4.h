#pragma once
#include <iostream>
class Vector4
{
public:
	Vector4();
	Vector4(float i_x, float i_y, float i_z, float i_w = 0.0f);
	Vector4 operator= (const Vector4& v);

	const Vector4 operator* (const float &scalar) const;
	const Vector4 operator+ (const Vector4 &v) const;
	const Vector4 Scale(const Vector4 &A, const Vector4 &B) const;
	
	float X() const { return px; };
	float Y() const { return py; };
	float Z() const { return pz; };
	float W() const { return pw; };
	
	friend std::ostream& operator<<(std::ostream& os, const Vector4& v4);
private:
	float px;
	float py;
	float pz;
	float pw;
};

