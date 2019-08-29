#pragma once
#include <iostream>
class Vector2
{
public:
	Vector2(float x, float y);
	Vector2();
	friend std::ostream& operator<<(std::ostream& os, const Vector2 v2);
	float x; 
	float y;

};

