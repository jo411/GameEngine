#include "Vector2.h"

Vector2::Vector2(float xin, float yin)
{
	x = xin;
	y = yin;
}

Vector2::Vector2()
{
	x = 0;
	y = 0;
}

Vector2 & Vector2::operator+(Vector2 rhs)
{
	return *(new Vector2(x + rhs.x, y + rhs.y));
}

//<< overload writes this Vector2 in the form:  "(x,y)"
std::ostream & operator<<(std::ostream & os, const Vector2 v2)
{
	os << "(" << v2.x << "," << v2.y<<")";
	return os;
}
