#pragma once
class RefCounter
{
public:
	void AddSmartRef()
	{
		SmartCount++;
	}

	void AddWeakRef()
	{
		WeakCount++;
	}

	int getSmartCount() { return SmartCount; }
	int getWeakCount() { return WeakCount; }

	int ReleaseSmart()
	{
		return --SmartCount;
	}
	int ReleaseWeak()
	{
		return --WeakCount;
	}

private:
	int SmartCount=0;
	int WeakCount = 0;
};

