#include "stdafx.h"
#include "CppUnitTest.h"
#include "Vector2.h"
#include "Floats.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include"Math/Matrix4.h"
#include "Math/Vector4.h"

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

		TEST_METHOD(FloatZeroADD)
		{
			float x = 0.0f;			

			for (int i = 0; i < 10; i++)
			{
				x += .1f;
			}
			x -= 1.0f;

			Assert::IsTrue(Floats::isZero(x));
		}		

		TEST_METHOD(FloatZeroPI)
		{
			float x = 0.0f;
			float y = 0.0f;

			x = sin(M_PI);

			Assert::IsTrue(Floats::isZero(x));
		}

		TEST_METHOD(FloatisNotNAN)
		{
			float A = sqrt(2);
			Assert::IsFalse(Floats::isNAN(A));
		}

		TEST_METHOD(FloatisNAN)
		{
			float A = sqrt(-2);
			Assert::IsTrue(Floats::isNAN(A));
		}

	};
}

namespace MatrixVectorTests
{
	TEST_CLASS(MatrixVectorTests)
	{
	public:
		TEST_METHOD(Template)
		{
			Assert::IsTrue(true);
		}

		TEST_METHOD(Equality)
		{
			Matrix4 identity;

			Matrix4 other(	1, 0, 0, 0,
							0, 1, 0, 0,
							0, 0, 1, 0,
							0, 0, 0, 1);
			Assert::IsTrue(identity == other);

		}

		TEST_METHOD(RotateX)
		{
			Matrix4 rotation = Matrix4::createRotationX(45);			
			Vector4 pos(1, 2, 3, 1);
			Vector4 transformed = rotation * pos;
			Vector4 result(1, -0.7071068, 3.535534);

			Assert::IsTrue(transformed == result);
		}
		TEST_METHOD(RotateY)
		{
			Matrix4 rotation = Matrix4::createRotationY(45);
			Vector4 pos(1, 3, 5, 1);
			Vector4 transformed = rotation * pos;
			Vector4 result(4.2426408, 3, 2.8284272);

			Assert::IsTrue(transformed == result);
		}
		TEST_METHOD(Scale)
		{
			Matrix4 scale = Matrix4::createScale(2, 2, 2);
			Vector4 pos(1, 1, 1, 1);
			Vector4 transformed = scale * pos;
			Vector4 result(2, 2, 2);
			Assert::IsTrue(transformed == result);
		}
		TEST_METHOD(Translate)
		{
			Matrix4 translation = Matrix4::createTranslation(10, 0, 0);
			Vector4 pos(10, 10, 10, 1);
			Vector4 transformed = translation * pos;
			Vector4 result(20, 10, 10);
			Assert::IsTrue(transformed == result);
		}
		TEST_METHOD(MxI)
		{
			Matrix4 I;
			Matrix4 random(1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6, 7);
			Matrix4 multiply = I * random;
			Assert::IsTrue(multiply == random);
		}
		TEST_METHOD(transpose)
		{
			Matrix4 random(1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6, 7);			
			Matrix4 transpose = random.getTranspose(false);
			Matrix4 result(1,5,9,4,2,6,1,5,3,7,2,6,4,8,3,7);
			Assert::IsTrue(transpose == result);
		}
		TEST_METHOD(InvertRotation)
		{
			Matrix4 rotation = Matrix4::createRotationX(45);
			Matrix4 invert = rotation.getTranspose(true);
			Vector4 pos(1, 2, 3, 1);
			Vector4 transformed = rotation * pos;
			Vector4 invertedPoint = invert * transformed;			

			Assert::IsTrue(invertedPoint == pos);
		}
		TEST_METHOD(InvertTranslation)
		{
			Vector4 point(1, 2, 3, 1);

			Matrix4 mTrans = Matrix4::createTranslation(12, 3, 5.5);
			Matrix4 mTransInverse = mTrans.getTranspose(true);
			
			Vector4 pointTranslate = mTrans * point; 

			Vector4 invertedPoint = mTransInverse *pointTranslate;

			Assert::IsTrue(invertedPoint == point);
		}

		TEST_METHOD(InvertOperationComplex)
		{
			Vector4 pointShip(1, 2, 3, 1);

			Matrix4 mRot = Matrix4::createRotationX(45);
			mRot = mRot* Matrix4::createRotationY(13);
			mRot = mRot * Matrix4::createRotationY(180);

			Matrix4 mTrans = Matrix4::createTranslation(12, 3, 5.5);			
			Matrix4 mShipToWorld = mTrans * mRot;
			

			Vector4 pointWorld = mShipToWorld * pointShip;

			Vector4 invertedPoint = (mShipToWorld.getTranspose(true)) * pointWorld;

			Assert::IsTrue(invertedPoint == pointShip);
		}

		TEST_METHOD(TransformationTesting)
		{
			Vector4 A(2, 1, 0, 1);
			Vector4 B(1, 2, 0, 1);			
			Vector4 CLocal(1, 1, 0, 1);					
			
			Matrix4 AToWorld = Matrix4::createTranslation(A.X(), A.Y(), 0);
			Matrix4 BToWorld = Matrix4::createTranslation(B.X(), B.Y(), 0);

			Vector4 CinWorldA = AToWorld * CLocal;
			Vector4 CinWorldB = BToWorld * CLocal;

			Matrix4 AToB = AToWorld * BToWorld.getTranspose(true);

			Vector4 CaB = AToB * CLocal;
			//Matrix 4 AToB = 

			Assert::IsTrue(true);
			
		}


	};
}