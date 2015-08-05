#include "../targetver.h"
#include "../specializations.h"
#include "CppUnitTest.h"

using namespace ApplicationInsights::CX;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Platform;
using namespace Windows::ApplicationModel;
using namespace Windows::Foundation;
using namespace Windows::Storage;

namespace CX {
	namespace tests
	{
		namespace ApplicationInsights
		{
			TEST_CLASS(TestCXApplication)
			{
			public:
				TEST_METHOD(CtorWorksAsExpected)
				{
					Application ^app = ref new Application();
				};

				TEST_METHOD(VerWorksAsExpected)
				{
					Application ^app = ref new Application();
					String ^expected = L"TEST";
					app->Ver = expected;
					Assert::AreEqual(expected, app->Ver);
				};

				TEST_METHOD(BuildWorksAsExpected)
				{
					Application ^app = ref new Application();
					String ^expected = L"TEST";
					app->Build = expected;
					Assert::AreEqual(expected, app->Build);
				};
			};
		}
	}
}
