#pragma once
class RefCounter
{
public:
	void AddRef()
	{
		count++;
	}

	int Release()
	{
		return --count;
	}

private:
	int count;
};

