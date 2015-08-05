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
			TEST_CLASS(TestCXSession)
			{
			public:
				TEST_METHOD(CtorWorksAsExpected)
				{
					Session ^session = ref new Session();
					Assert::AreEqual(L"True", session->IsFirst);
					Assert::AreEqual(L"True", session->IsNew);

					wre sessionUuidMatcher(L"(\\{){0,1}[0-9a-fA-F]{8}-[0-9a-fA-F]{4}-[0-9a-fA-F]{4}-[0-9a-fA-F]{4}-[0-9a-fA-F]{12}(\\}){0,1}");
					std::wstring sessionUuid = session->Id->Data();
					Assert::IsTrue(wre_match(sessionUuid, sessionUuidMatcher), L"Invalid regex for session uuid");
				};

				TEST_METHOD(IsFirstWorksAsExpected)
				{
					Session ^session = ref new Session();
					String ^expected = L"TEST";
					session->IsFirst = expected;
					Assert::AreEqual(expected, session->IsFirst);
				};

				TEST_METHOD(IsNewWorksAsExpected)
				{
					Session ^session = ref new Session();
					String ^expected = L"TEST";
					session->IsNew = expected;
					Assert::AreEqual(expected, session->IsNew);
				};
			};
		}
	}
}
