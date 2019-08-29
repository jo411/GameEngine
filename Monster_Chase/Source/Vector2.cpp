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


std::ostream & operator<<(std::ostream & os, const Vector2 v2)
{
	os << "(" << v2.x << "," << v2.y<<")";
	return os;
}
