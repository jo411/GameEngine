#pragma once
#include <iostream>
//The Simple String is a memory managed char* wrapper for some easier handling of strings.

class SimpleString
{
	char* string=NULL;//The current string's pointer in memory
	int length=-1;//The length of the current string	
	void nullTerminate();//Ensures the current string is null terminated
	void copyString(const SimpleString& other);//Copies the contents of one simplestring to another. (Called from the assignment operator and copy constructor)
public:
	void append(char newChar);//Appends the given char into this string
	char charAt(int index) const;//Gets the character at index if possible
	SimpleString();
	~SimpleString();
	char* getCharArray();//Returns the char* of this SimpleString in its current state
	SimpleString(const SimpleString& other);//Copy constructor
	SimpleString(const char* string);//char* constructor
	SimpleString& operator=(const SimpleString& other);//Assignment operator
	friend std::ostream& operator<<(std::ostream& os, const SimpleString ss);//<< overload
	void fromCharArray(const char* newString);//Forces this SimpleString to take on the string provided. Freeing any previous state.	
	int getLength() const;//Gets the length of this string (ignoring the null terminator)
};

