#include "targetver.h"
#include "specializations.h"
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
			TEST_CLASS(TestCXUser)
			{
			public:
				TEST_METHOD(CtorWorksAsExpected)
				{
					User ^user = ref new User();
					Assert::IsTrue(user->AccountAcquisitionDate != nullptr);
					wre idMatcher(L"(\\{){0,1}[0-9a-fA-F]{8}-[0-9a-fA-F]{4}-[0-9a-fA-F]{4}-[0-9a-fA-F]{4}-[0-9a-fA-F]{12}(\\}){0,1}");
					std::wstring id = user->Id->Data();
					Assert::IsTrue(wre_match(id, idMatcher), L"Invalid regex for user id");
				};

				TEST_METHOD(AccountIdWorksAsExpected)
				{
					User ^user = ref new User();
					String ^expected = L"TEST";
					user->AccountId = expected;
					Assert::AreEqual(expected, user->AccountId);
				};
				
				TEST_METHOD(UserAgentWorksAsExpected)
				{
					User ^user = ref new User();
					String ^expected = L"TEST";
					user->UserAgent = expected;
					Assert::AreEqual(expected, user->UserAgent);
				};

				TEST_METHOD(StoreRegionWorksAsExpected)
				{
					User ^user = ref new User();
					String ^expected = L"TEST";
					user->StoreRegion = expected;
					Assert::AreEqual(expected, user->StoreRegion);
				};
			};
		}
	}
}
