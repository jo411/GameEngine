#include "stdafx.h"
#include "CppUnitTest.h"
#include "Vector2.h"
#include "Floats.h"
#define _USE_MATH_DEFINES
#include <math.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(Add)
		{
			Vector2 a = *new Vector2(1, 2);
			Vector2 b = *new Vector2(2, 4);
			a = a + b;
			Assert::AreEqual(float(3), a.x);
			Assert::AreEqual(float(6), a.y);
		}
		TEST_METHOD(Subtract)
		{
			Vector2 a = *new Vector2(1, 4);
			Vector2 b = *new Vector2(2, 2);
			a = a - b;
			Assert::AreEqual(float(-1), a.x);
			Assert::AreEqual(float(2), a.y);
		}
		TEST_METHOD(UnaryMinus)
		{
			Vector2 a = *new Vector2(1, -4);
			a = -a;
			Assert::AreEqual(float(-1), a.x);
			Assert::AreEqual(float(4), a.y);
		}
		TEST_METHOD(Multiply)
		{
			Vector2 a = *new Vector2(1, 4);
			Vector2 b = *new Vector2(2, 2);
			a = a * b;
			Assert::AreEqual(float(2), a.x);
			Assert::AreEqual(float(8), a.y);
		}
		TEST_METHOD(Scale)
		{
			Vector2 a = *new Vector2(1, -4);
			a = a*2;
			Assert::AreEqual(float(2), a.x);
			Assert::AreEqual(float(-8), a.y);

		}
		TEST_METHOD(ScaleF)
		{

			Vector2 a = *new Vector2(1, -4);			
			a = a * .5f;
			Assert::AreEqual(float(.5), a.x);
			Assert::AreEqual(float(-2), a.y);
		}
		TEST_METHOD(ScaleD)
		{
			Vector2 a = *new Vector2(1, -4);
			a = a * .5;
			Assert::AreEqual(float(.5), a.x);
			Assert::AreEqual(float(-2), a.y);			
		}
		TEST_METHOD(Divide)
		{
			Vector2 a = *new Vector2(1, -4);
			Vector2 b = *new Vector2(2, 4);
			a = a /b;
			Assert::AreEqual(float(.5), a.x);
			Assert::AreEqual(float(-1), a.y);
		}
		TEST_METHOD(CompareTrue)
		{
			Vector2 a = *new Vector2(1, -4);
			Vector2 b = *new Vector2(1, -4);
			Assert::IsTrue(a ==b);
		}
		TEST_METHOD(CompareFalse)
		{
			Vector2 a = *new Vector2(1, 5);
			Vector2 b = *new Vector2(2, 4);
			Assert::IsFalse(a == b);
		}
		TEST_METHOD(notEqTrue)
		{
			Vector2 a = *new Vector2(1, 5);
			Vector2 b = *new Vector2(2, 4);
			Assert::IsTrue(a != b);
		}
		TEST_METHOD(notEqFalse)
		{
			Vector2 a = *new Vector2(1, 5);
			Vector2 b = *new Vector2(1, 5);
			Assert::IsFalse(a != b);
		}
		TEST_METHOD(GreaterThan)
		{
			Vector2 a = *new Vector2(1, 2);
			Vector2 b = *new Vector2(2, 4);
			Assert::IsFalse(a > b);
			Assert::IsTrue(b>a);

		}
		TEST_METHOD(LessThan)
		{
			Vector2 a = *new Vector2(1, 2);
			Vector2 b = *new Vector2(2, 4);
			Assert::IsTrue(a < b);
			Assert::IsFalse(b < a);

		}
		TEST_METHOD(GreaterThanEq)
		{
			Vector2 a = *new Vector2(2, 4);
			Vector2 b = *new Vector2(2, 4);			
			Assert::IsTrue(b >= a);
		}
		TEST_METHOD(LessThanEq)
		{
			Vector2 a = *new Vector2(2, 4);
			Vector2 b = *new Vector2(2, 4);
			Assert::IsTrue(b <= a);
		}
		TEST_METHOD(plusEq)
		{
			Vector2 a = *new Vector2(1, 2);
			Vector2 b = *new Vector2(2, 4);
			a+=b;
			Assert::AreEqual(float(3), a.x);
			Assert::AreEqual(float(6), a.y);
		}
		TEST_METHOD(minusEq)
		{
			Vector2 a = *new Vector2(1, 2);
			Vector2 b = *new Vector2(2, 4);
			a -= b;
			Assert::AreEqual(float(-1), a.x);
			Assert::AreEqual(float(-2), a.y);
		}
		TEST_METHOD(MultiplyEq)
		{
			Vector2 a = *new Vector2(1, 4);
			Vector2 b = *new Vector2(2, 2);
			a*= b;
			Assert::AreEqual(float(2), a.x);
			Assert::AreEqual(float(8), a.y);
		}
		TEST_METHOD(DivideEq)
		{
			Vector2 a = *new Vector2(1, -4);
			Vector2 b = *new Vector2(2, 4);
			a/= b;
			Assert::AreEqual(float(.5), a.x);
			Assert::AreEqual(float(-1), a.y);
		}
		TEST_METHOD(ScaleEq)
		{
			Vector2 a = *new Vector2(1, -4);
			a *= 2;
			Assert::AreEqual(float(2), a.x);
			Assert::AreEqual(float(-8), a.y);

		}
		TEST_METHOD(ScaleFEq)
		{

			Vector2 a = *new Vector2(1, -4);
			a *=.5f;
			Assert::AreEqual(float(.5), a.x);
			Assert::AreEqual(float(-2), a.y);
		}
		TEST_METHOD(ScaleDEq)
		{
			Vector2 a = *new Vector2(1, -4);
			a *= .5;
			Assert::AreEqual(float(.5), a.x);
			Assert::AreEqual(float(-2), a.y);
		}

		TEST_METHOD(officialTests)
		{
			Vector2 P1(1.0f, 5.4f);
			Vector2 P2(2.0f, 0.3f);

			Vector2 P3 = P1 + P2;
			P3 = P1 - P2;

			Vector2 P4 = P1 * 0.5f;

			Vector2 P5 = P1 / 2.0f;

			Vector2 P6 = -P4;

			P6 *= 2.0f;
			P5 /= 4.0f;

			P2 += P1;
			P3 -= P1;

			Vector2 P7 = (((P1 + P2) * 2.0f) - -P3) / 2.0f;

			bool bArentEqual = P6 != P4;

			Assert::IsTrue(bArentEqual);
		}

		TEST_METHOD(constCorrect)
		{
			Vector2 P1(1.0f, 5.4f);
			Vector2 P2(2.0f, 0.3f);

			Vector2 P3 = P1 + P2;
			P3 = P1 - P2;

			Vector2 P4 = P1 * 0.5f;

			Vector2 P5 = P1 / 2.0f;

			Vector2 P6 = -P4;

			P6 *= 2.0f;
			P5 /= 4.0f;

			P2 += P1;
			P3 -= P1;

			Vector2 P7 = (((P1 + P2) * 2.0f) - -P3) / 2.0f;

			bool sameVal = P1.x == 1.0f && P1.y == 5.4f;
			Assert::IsTrue(sameVal);
			
		}
	};
}

namespace FloatTests
{
	TEST_CLASS(FloatTests)
	{
	public:
		TEST_METHOD(FloatEq1)
		{
			float x = 1.0f;
			float y = 0 + 1;
			Assert::IsTrue(Floats::RelativeEpsilonEqual(x,y));
		}

		TEST_METHOD(FloatEq2)
		{
			float x = 100/300.0f;
			float y = 1.0f/3.0f;
			Assert::IsTrue(Floats::RelativeEpsilonEqual(x, y));
		}

		TEST_METHOD(FloatEq3)
		{
			float x = 0.0f;
			float y = 1.0f;

			for (int i = 0; i < 10; i++)
			{
				x += .1f;
			}

			Assert::IsTrue(Floats::RelativeEpsilonEqual(x, y));
		}

		TEST_METHOD(FloatEq4)
		{
			float x = 0.0f;			

			for (int i = 0; i < 10; i++)
			{
				x += .1f;
			}
			x -= 1.0f;

			Assert::IsTrue(Floats::isZero(x));
		}		

		TEST_METHOD(FloatEq5)
		{
			float x = 0.0f;
			float y = 0.0f;

			x = sin(M_PI);

			Assert::IsTrue(Floats::isZero(x));
		}

	};
}