#include "HighResolutionTimer.h"
#include <Windows.h>
void HighResolutionTimer::StartCounter()
{
	LARGE_INTEGER largeInt;

	QueryPerformanceFrequency(&largeInt);

	freq = double(largeInt.QuadPart) / 1000.0;

	QueryPerformanceCounter(&largeInt);
	CounterStart = largeInt.QuadPart;
		
}

double HighResolutionTimer::GetCounter()
{
	LARGE_INTEGER largeInt;
	QueryPerformanceCounter(&largeInt);
	return double(largeInt.QuadPart - CounterStart) / freq;
}
