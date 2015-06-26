#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestApp
{
    TEST_CLASS(UnitTest1)
    {
    public:
        TEST_METHOD(TestMethod1)
        {
			Assert::AreEqual(0, 1, L"0 does not eqaul 1");
            // TODO: Your test code here
        }
    };
}