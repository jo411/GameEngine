#pragma once
#include <iostream>
//A Vector2 holds two dimensional positions.

class Vector2
{
public:
	
	float x; 
	float y;

	Vector2(float x, float y);
	Vector2();
	//Operators
	friend std::ostream& operator<<(std::ostream& os, const Vector2 v2);//cout operator
	Vector2& operator+(Vector2 rhs);
};

