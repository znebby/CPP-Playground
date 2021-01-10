#include "CppUnitTest.h"
#include "../Lib/utils.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Ultra;

namespace UnitTest
{		
	TEST_CLASS(AddTest)
	{

	public:
		
		TEST_METHOD(DoubleZeroTest)
		{
			Assert::AreEqual(utils::add(0, 0), 0);
		}

		TEST_METHOD(SingleZeroTest)
		{
			Assert::AreEqual(utils::add(13, 0), 13);
		}

		TEST_METHOD(SingleZeroTest2)
		{
			Assert::AreEqual(utils::add(0, 13), 13);
		}
		
		TEST_METHOD(SimpleTest)
		{
			Assert::AreEqual(utils::add(2, 2), 4);
		}

		TEST_METHOD(OrderTest)
		{
			Assert::AreEqual(utils::add(5, 21), utils::add(21, 5));
		}

		TEST_METHOD(NegativeTest)
		{
			Assert::AreEqual(utils::add(-4, -11), -15);
		}

		TEST_METHOD(PositiveAndNegativeTest)
		{
			Assert::AreEqual(utils::add(5, -12), -7);
		}

		TEST_METHOD(PositiveAndNegativeTest2)
		{
			Assert::AreEqual(utils::add(-5, 12), 7);
		}

		TEST_METHOD(PositiveAndNegativeTest3)
		{
			Assert::AreEqual(utils::add(-1, 1), 0);
		}

		TEST_METHOD(PositiveOverflowTest)
		{
			auto func = [] { utils::add(INT_MAX, 1); };
			Assert::ExpectException<std::overflow_error>(func);
		}

		TEST_METHOD(PositiveOverflowTest2)
		{
			auto func = [] { utils::add(INT_MAX, INT_MAX); };
			Assert::ExpectException<std::overflow_error>(func);
		}

		TEST_METHOD(PositiveOverflowTest3)
		{
			auto func = [] { utils::add(INT_MAX/2+1, INT_MAX/2+1); };
			Assert::ExpectException<std::overflow_error>(func);
		}

		TEST_METHOD(NegativeOverflowTest)
		{
			auto func = [] { utils::add(INT_MIN, -1); };
			Assert::ExpectException<std::overflow_error>(func);
		}

		TEST_METHOD(NegativeOverflowTest2)
		{
			auto func = [] { utils::add(INT_MIN, INT_MIN); };
			Assert::ExpectException<std::overflow_error>(func);
		}

		TEST_METHOD(NegativeOverflowTest3)
		{
			auto func = [] { utils::add(INT_MIN/2-1, INT_MIN/2-1); };
			Assert::ExpectException<std::overflow_error>(func);
		}

		TEST_METHOD(MaxIntTest)
		{
			Assert::AreEqual(utils::add(INT_MAX, -1), INT_MAX-1);
		}

		TEST_METHOD(MinIntTest)
		{
			Assert::AreEqual(utils::add(INT_MIN, 1), INT_MIN + 1);
		}

		TEST_METHOD(MaxAndMinIntTest)
		{
			Assert::AreEqual(utils::add(INT_MAX, INT_MIN), -1);
		}

	};
}