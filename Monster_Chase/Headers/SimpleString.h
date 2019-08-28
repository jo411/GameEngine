#pragma once
class SimpleString
{
	char* string;
	int length;

	~SimpleString();
	void nullTerminate();
	void copyString(const SimpleString& other);
public:
	void append(char newChar);	
	char charAt(int index) const;

	SimpleString();
	SimpleString(const SimpleString& other);
	SimpleString(const char* string);
	SimpleString& operator=(const SimpleString& other);
	
	int getLength() const;
};

