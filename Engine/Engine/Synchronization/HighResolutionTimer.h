#pragma once
class HighResolutionTimer
{
public:

	void StartCounter();
	double GetCounter();

private:
	double freq = 0.0;
	__int64 CounterStart;


};

