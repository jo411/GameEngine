#include "Vector2.h"


Vector2::Vector2(float i_x, float i_y):x(i_x), y(i_y)
{
}


inline float Vector2::magnitude()const
{
	return sqrt(x*x + y * y);
}

Vector2 Vector2::operator+(const Vector2& rhs) const
{
	return  Vector2(x + rhs.x, y + rhs.y);
}

Vector2 Vector2::operator-(const Vector2& rhs)const
{
	return Vector2(x - rhs.x, y - rhs.y);
}

Vector2 Vector2::operator-()const
{
	return Vector2(-x, -y);
}

Vector2 Vector2::operator*(const Vector2& rhs)const
{
	return  Vector2(x * rhs.x, y * rhs.y);
}



Vector2 Vector2::operator*(int scalar)const
{
	return Vector2(x * scalar, y * scalar);
}

Vector2 Vector2::operator*(float scalar)const
{
	return Vector2(x * scalar, y * scalar);
}

Vector2 Vector2::operator*(double scalar)const
{
	return  Vector2(x * (float)scalar, y * (float)scalar);
}

Vector2 Vector2::operator/(const Vector2& rhs)const
{
	return Vector2(x / rhs.x, y / rhs.y);
}

Vector2 Vector2::operator/(int scalar)const
{
	return Vector2(x / (float)scalar, y / (float)scalar);
}

Vector2 Vector2::operator/(float scalar)const
{
	return  Vector2(x / scalar, y / scalar);
}

Vector2 Vector2::operator/(double scalar)const
{
	return Vector2(x / (float)scalar, y / (float)scalar);
}


bool Vector2::operator==(const Vector2& rhs) const
{
	return (x == rhs.x && y == rhs.y);
}

bool Vector2::operator!=(const Vector2& rhs) const
{
	return !(x == rhs.x && y == rhs.y);
}

bool Vector2::operator>(const Vector2& rhs) const
{
	return (magnitude() > rhs.magnitude());
}

bool Vector2::operator<(const Vector2& rhs) const
{
	return (magnitude() < rhs.magnitude());
}

bool Vector2::operator>=(const Vector2& rhs) const
{
	
	return ((*this==rhs)|| (magnitude() > rhs.magnitude()));
}

bool Vector2::operator<=(const Vector2& rhs) const
{
	return ((*this == rhs) || (magnitude() < rhs.magnitude()));
}

Vector2 & Vector2::operator+=(const Vector2& rhs)
{
	x += rhs.x;
	y += rhs.y;
	return *this;
}

Vector2 & Vector2::operator-=(const Vector2& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	return *this;
}

Vector2 & Vector2::operator*=(const Vector2& rhs)
{
	x *= rhs.x;
	y *= rhs.y;
	return *this;
}

Vector2 & Vector2::operator*=(int scalar)
{
	x *= (float)scalar;
	y *= (float)scalar;
	return *this;
}

Vector2 & Vector2::operator*=(float scalar)
{
	x *= scalar;
	y *= scalar;
	return *this;
}

Vector2 & Vector2::operator*=(double scalar)
{
	x *= (float)scalar;
	y *= (float)scalar;
	return *this;
}

Vector2 & Vector2::operator/=(const Vector2& rhs)
{
	x /= rhs.x;
	y /= rhs.y;
	return *this;
}

Vector2 & Vector2::operator/=(int scalar)
{
	x /= (float)scalar;
	y /= (float)scalar;
	return *this;
}

Vector2 & Vector2::operator/=(float scalar)
{
	x /= scalar;
	y /= scalar;
	return *this;
}

Vector2 & Vector2::operator/=(double scalar)
{
	x /= (float)scalar;
	y /= (float)scalar;
	return *this;
}
//<< overload writes this Vector2 in the form:  "(x,y)"
std::ostream & operator<<(std::ostream & os, const Vector2& v2)
{
	os << "(" << v2.x << "," << v2.y<<")";
	return os;
}
