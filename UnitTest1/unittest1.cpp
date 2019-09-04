#include "stdafx.h"
#include "CppUnitTest.h"
#include "Engine\Vector2.h"

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

	};
}