#include "SimpleString.h"
#include <malloc.h>
#include <iostream>
//Initializes the state of this string to a single char ('\0')
SimpleString::SimpleString()
{	
	length = 1;
	string =(char*) malloc(sizeof(char) * length);
	nullTerminate();
}

//free the char*
SimpleString::~SimpleString()
{
	free(string);
}

//Assignment operator just calls the copy function
SimpleString& SimpleString::operator=(const SimpleString& rightSide)
{	
	if (this != &rightSide)
	{
		copyString(rightSide);
	}

	return *this;
}

//Sets the state of this SS to the char* provided
void SimpleString::fromCharArray(const char * newString)
{
	free(string);//free any memory
	int len = 0;
	int i = 0;
	while (newString[i] != '\0')//count how long the new char* is 
	{
		len++;
		i++;
	}
	len++;//include nullterminator
	string = (char*)malloc(sizeof(char)*len);//allocate enough memory 

	if (string == NULL)
	{
		return;//malloc failed should throw in the future
	}

	for (int j = 0; j < len; j++)//copy chars from new to old
	{
		string[j] = newString[j];
	}
	length = len;//update the length
}

//Copy constructor just calls the copy function
SimpleString::SimpleString(const SimpleString& other)
{	
	string = NULL;
	copyString(other);	
}

//Allow a SS to be constructed from a char*
SimpleString::SimpleString(const char* newString)
{
	fromCharArray(newString);
}


//Return the char* for this string 
char * SimpleString::getCharArray()
{
	return string;
}

//Ensures the current string is null terminated
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
	string = (char*)malloc(length*sizeof(char));//allocate enough new memory
	if (string == NULL)//if malloc fails need to do something better . Throw something
	{
		return;
	}
	for (int i = 0; i < length; i++)//copy chars
	{
#pragma warning(suppress: 6386)//seems to be a false positive
		string[i] = other.charAt(i);
	}
}

//Gets the length of this string (ignoring the null terminator)
int SimpleString::getLength() const
{
	return length-1;//ignore null terminator
}

//Appends the given char into this string
void SimpleString::append(char newChar)
{
	char* newString =(char*)realloc(string, sizeof(char) * length + 1);//realloc with one more char
	if (newString == NULL)//if malloc fails need to do something better . Throw something
	{
		return;
	}
	string = newString;

	string[length-1] = newChar;
	length++;
	nullTerminate();
}

//Gets the character at index if possible
char SimpleString::charAt(int index) const
{
	if (index < length - 1)//ignore null terminator
	{
		return string[index];
	}
	else//bad index
	{
		return '\0';
	}
}

//<< overload writes this string
std::ostream & operator<<(std::ostream & os, const SimpleString ss)
{
	os << ss.string;
	return os;
}
