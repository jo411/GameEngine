#pragma once
#include <float.h>
#include<cmath>
class Floats
{
public:
	static inline bool RelativeEpsilonEqual(float A, float B, float maxDiff = 0.0f, float maxRelDiff = FLT_EPSILON)
	{
		float diff = fabs(A - B);
		if (diff <= maxDiff)
		{
			return true;
		}

		A = fabs(A);
		B = fabs(B);
		float max = (B > A) ? B : A;

		if (diff <= max * maxRelDiff)
		{
			return true;
		}
		return false;
	}

	static inline bool isZero(float A)
	{
		return RelativeEpsilonEqual(A, 0.0f, .000001f);
	}

	static inline bool isNAN(float A)
	{
		return A == A;
	}

};

