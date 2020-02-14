#pragma once
#include <stdio.h>
#include <Windows.h>

class Person
{
	int age;
	const char* pName;

public:
	Person() : pName(0), age(0)
	{
	}
	Person(const char* pName, int age) : pName(pName), age(age)
	{
	}
	~Person()
	{
	}

	void Display()
	{
		printf("Name = %s Age = %d \n", pName, age);

		const size_t	lenBuffer = 65;
		char			Buffer[lenBuffer];

		sprintf_s(Buffer, lenBuffer, "My name is %s, I am %d Years old.\n", pName, age);
		OutputDebugStringA(Buffer);


	}
};