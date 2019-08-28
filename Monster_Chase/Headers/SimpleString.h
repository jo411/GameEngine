#pragma once
#include <iostream>
class SimpleString
{
	char* string;
	int length;

	
	void nullTerminate();
	void copyString(const SimpleString& other);
public:
	void append(char newChar);	
	char charAt(int index) const;

	SimpleString();
	~SimpleString();
	SimpleString(const SimpleString& other);
	SimpleString(const char* string);
	SimpleString& operator=(const SimpleString& other);
	friend std::ostream& operator<<(std::ostream& os, const SimpleString ss);
	
	int getLength() const;
};

