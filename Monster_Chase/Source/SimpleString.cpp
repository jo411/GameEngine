#include "SimpleString.h"
#include <malloc.h>
#include <iostream>
SimpleString::SimpleString()
{	
	length = 1;
	string =(char*) malloc(sizeof(char) * length);
	nullTerminate();
}

SimpleString& SimpleString::operator=(const SimpleString& rightSide)
{	
	if (this != &rightSide)
	{
		copyString(rightSide);
	}

	return *this;
}

void SimpleString::fromCharArray(const char * newString)
{
	int len = 0;
	int i = 0;
	while (newString[i] != '\0')
	{
		len++;
		i++;
	}
	len++;
	string = (char*)malloc(sizeof(char)*len);

	for (int j = 0; j < len; j++)
	{
		string[j] = newString[j];
	}
	length = len;
}

SimpleString::SimpleString(const SimpleString& other)
{
	string = NULL;
	copyString(other);	
}

SimpleString::SimpleString(const char* newString)
{
	fromCharArray(newString);
}

SimpleString::~SimpleString()
{
	free(string);
}

char * SimpleString::getCharArray()
{
	return string;
}

void SimpleString::nullTerminate()
{
	string[length - 1] = '\0';
}

//Set this strings text to the others with a deep copy freeing the current memory if needed
void SimpleString::copyString(const SimpleString& other)
{
	free(string);
	string = NULL;
	length = other.getLength() + 1;
	string = (char*)malloc(sizeof(char) * length);

	for (int i = 0; i < length; i++)
	{
		string[i] = other.charAt(i);
	}
}

int SimpleString::getLength() const
{
	return length-1;//ignore null terminator
}


void SimpleString::append(char newChar)
{
	string =(char*)realloc(string, sizeof(char) * length + 1);
	string[length-1] = newChar;
	length++;
	nullTerminate();
}

char SimpleString::charAt(int index) const
{
	if (index < length - 1)//ignore null terminator
	{
		return string[index];
	}
	else
	{
		return '\0';
	}
}

std::ostream & operator<<(std::ostream & os, const SimpleString ss)
{
	os << ss.string;
	return os;
}
