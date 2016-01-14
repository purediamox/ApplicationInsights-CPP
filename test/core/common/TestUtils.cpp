//#include "../targetver.h"
//#include "../specializations.h"
#include "CppUnitTest.h"
#include "common/Utils.h"

using namespace ApplicationInsights::core;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace core { namespace tests { namespace common
{
    TEST_CLASS(TestUtils)
    {
    public:
        
        TEST_METHOD(UtilsUTFConversions)
        {
			std::wstring ABC_W = L"Abc";

			std::string ABC = "Abc";

			std::string result = Utils::ConvertToUtf8(ABC_W);
			Assert::AreEqual(ABC, result);
            
			std::wstring result2 = Utils::ConvertToUtf16(ABC);
			Assert::AreEqual(ABC_W, result2);
			
        };

    };
}}}
