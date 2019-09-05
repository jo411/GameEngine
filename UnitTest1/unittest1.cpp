#include "stdafx.h"
#include "CppUnitTest.h"
#include "Vector2.h"

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
			a *=.5;
			Assert::AreEqual(float(.5), a.x);
			Assert::AreEqual(float(-2), a.y);
		}
	};
}