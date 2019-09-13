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

	float magnitude()const;
	//Operators
	friend std::ostream& operator<<(std::ostream& os, const Vector2 v2);//cout operator

	//Arithmatic
	Vector2 operator+(Vector2 rhs);//a+b
	Vector2 operator-(Vector2 rhs);//a-b
	Vector2 operator-();//-a
	Vector2 operator*(Vector2 rhs);//a*b
	Vector2 operator*(int scalar);//a*b
	Vector2 operator*(float scalar);//a*b
	Vector2 operator*(double scalar);//a*b
	Vector2 operator/(Vector2 rhs);//a/b
	Vector2 operator/(int scalar);//a/b
	Vector2 operator/(float scalar);//a/b
	Vector2 operator/(double scalar);//a/b

	//Comparison
	bool operator ==(const Vector2 rhs)const; //a==b
	bool operator !=(const Vector2 rhs)const; //a!=b
	bool operator >(const Vector2 rhs)const; //a>b
	bool operator <(const Vector2 rhs)const; //a<b
	bool operator >=(const Vector2 rhs)const; //a>=b
	bool operator <=(const Vector2 rhs)const; //a<=b

	//Compound assignment
	Vector2& operator+=(Vector2 rhs);//a=a+b
	Vector2& operator-=(Vector2 rhs);//a=a-b
	Vector2& operator*=(Vector2 rhs);//a=a*b
	Vector2& operator*=(int scalar);//a*b
	Vector2& operator*=(float scalar);//a*b
	Vector2& operator*=(double scalar);//a*b
	Vector2& operator/=(int scalar);//a=a/b
	Vector2& operator/=(Vector2 rhs);//a=a/b
	Vector2& operator/=(float scalar);//a=a/b
	Vector2& operator/=(double scalar);//a=a/b
};

